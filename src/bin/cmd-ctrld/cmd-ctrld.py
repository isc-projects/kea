import http.server
import urllib.parse
import json
import re
import ssl, socket
import ISC
import pprint
import select
import csv
import random
from hashlib import sha1

try:
    import threading
except ImportError:
    import dummy_threading as threading

URL_PATTERN = re.compile('/([\w]+)(?:/([\w]+))?/?')
        
class SecureHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    '''
    Process GET and POST
    '''
        
    def parse_path(self, path):
        groups = URL_PATTERN.match(path) 
        if not groups:
            return (NULL, NULL)

        return (groups.group(1), groups.group(2))

    def check_username(self,name):
        reader = csv.reader(open("passwd.csv"), delimiter="\t", quoting=csv.QUOTE_MINIMAL)
        for row in reader:
            if name==row[0]:
                self.user=[row[0],row[1],row[2]]
                return 1
        return 0


    def check(self):
        length = self.headers.get('content-length')
        nbytes = int(length)
        user_info = json.loads((self.rfile.read(nbytes)).decode())

        if not user_info:
            return ["error: invalid username or password"], http.client.UNAUTHORIZED
        if not self.check_username(user_info['username']):
            return ["error:the username doesn't exists"], http.client.UNAUTHORIZED

        if sha1((user_info['password'] + self.user[2]).encode()).hexdigest() != self.user[1] :
            return ["error:the username and passwd did not match!"], http.client.UNAUTHORIZED
        else :
            id = self.headers.get('cookie')
            self.server.session[id]['username'] = user_info['username']
            return ["login success !"], http.client.OK


    def do_GET(self):
        id = self.headers.get('cookie')
        if id not in self.server.session:
            self.server.session[id]={}
        
        reply_value = []
        if "username" not in self.server.session[id]:
            reply_value = ["please post username and passwd"]
        else:
            identifier, module = self.parse_path(self.path)
            if identifier != None:
                data = self.server.get_reply_data_for_GET(identifier, module) 
                if data:
                    reply_value = data

        self.send_response(200)
        self.end_headers()
        self.wfile.write(json.dumps(reply_value).encode())

        
    def do_POST(self):
        id = self.headers.get('cookie')
        if id not in self.server.session:
            self.server.session[id] = {}

        reply_msg = []
        rcode = 200
        if self.path == '/login':
            reply_msg, rcode = self.check()
        elif "username" not in self.server.session[id]:
            reply_msg, rcode = ["please login!"], http.client.UNAUTHORIZED
        else:
            mod, cmd = self.parse_path(self.path)
            param = None
            len = self.headers.get('Content-Length')
            if len:
                post_str = str(self.rfile.read(int(len)).decode())
                print("command parameter:%s" % post_str)
                param = json.loads(post_str)

            reply_msg = self.server.send_command_to_module(mod, cmd, param)
            print('cmd-ctrld finish send message \'%s\' to module %s' % (cmd, mod))
        
        #TODO, set proper rcode
        self.send_response(rcode)
        self.end_headers()
        self.wfile.write(json.dumps(reply_msg).encode())

class CommandControl():
    def __init__(self):
        self.cc = ISC.CC.Session()
        self.cc.group_subscribe('Cmd-Ctrld')
        #self.cc.group_subscribe('Boss', 'Cmd-Ctrld')
        self.command_spec = self.get_cmd_specification()
        self.config_spec = self.get_data_specification()
        self.config_data = self.get_config_data()

    def get_cmd_specification(self): 
        return self.send_command('ConfigManager', 'get_commands')

    def get_config_data(self):
        return self.send_command('ConfigManager', 'get_config')

    def update_config_data(self, module_name, command_name):
        if module_name == 'ConfigManager' and command_name == 'set_config':
            self.config_data = self.get_config_data()

    def get_data_specification(self):
        return self.send_command('ConfigManager', 'get_data_spec')

    def handle_recv_msg(self):
        # Handle received message, if 'shutdown' is received, return False
        (message, env) = self.cc.group_recvmsg(True)
        while message:
            if 'commands_update' in message:
                self.command_spec[message['commands_update'][0]] = message['commands_update'][1]
            elif 'specification_update' in message:
                msgvalue = message['specification_update']
                self.config_spec[msgvalue[0]] = msgvalue[1]
            elif 'command' in message and message['command'][0] == 'shutdown':
                return False;
            (message, env) = self.cc.group_recvmsg(True)
        
        return True
    
    def send_command(self, module_name, command_name, params = None):
        content = [command_name]
        if params:
            content.append(params)

        msg = {'command' : content}
        print('cmd-ctrld send command \'%s\' to %s' %(command_name, module_name))
        try:
            self.cc.group_sendmsg(msg, module_name)
            answer, env = self.cc.group_recvmsg(False)
            if answer and 'result' in answer.keys() and type(answer['result']) == list:
                # TODO: with the new cc implementation, replace "1" by 1
                if answer['result'][0] == "1":
                    # todo: exception
                    print("Error: " + str(answer['result'][1]))
                    return {}
                else:
                    self.update_config_data(module_name, command_name)
                    if len(answer['result']) > 1:
                        return answer['result'][1]
                    return {}
            else:
                print("Error: unexpected answer from %s" % module_name)
        except Exception as e:
            print(e)
            print('cmd-ctrld fail send command \'%s\' to %s' % (command_name, module_name))
        return {}


class SecureHTTPServer(http.server.HTTPServer):
    '''Make the server address can be reused.'''
    allow_reuse_address = True

    def __init__(self, server_address, RequestHandlerClass):
        http.server.HTTPServer.__init__(self, server_address, RequestHandlerClass)
        self.session = {}
        self.cmdctrl = CommandControl()
        self.__is_shut_down = threading.Event()
        self.__serving = False

    def get_request(self):
        newsocket, fromaddr = self.socket.accept()
        try:
            connstream = ssl.wrap_socket(newsocket,
                                     server_side = True,
                                     certfile = 'create_your_cert.pem',
                                     keyfile = 'create_your_cert.pem',
                                     ssl_version = ssl.PROTOCOL_SSLv23)
            return (connstream, fromaddr)
        except ssl.SSLError as e :
            print("error happen***********")
            print(e)
            
    
    def get_reply_data_for_GET(self, id, module_name):
        if module_name is None:
            if id == 'command_spec':
                return self.cmdctrl.command_spec
            elif id == 'config_data':
                return self.cmdctrl.config_data
            elif id == 'config_spec':
                return self.cmdctrl.config_spec
            else:
                return None

    def serve_forever(self, poll_interval = 0.5):
        self.__serving = True
        self.__is_shut_down.clear()
        while self.__serving:
            if not self.cmdctrl.handle_recv_msg():
                break

            r, w, e = select.select([self], [], [], poll_interval)
            if r:
                self._handle_request_noblock()

        self.__is_shut_down.set()
    
    def shutdown(self):
        self.__serving = False
        self.__is_shut_down.wait()


    def send_command_to_module(self, module_name, command_name, params):
        return self.cmdctrl.send_command(module_name, command_name, params)

def run(server_class = SecureHTTPServer, addr = 'localhost', port = 8080):
    print("cmd-ctrld module is starting on :%s port:%d" %(addr, port))
    httpd = server_class((addr, port), SecureHTTPRequestHandler)
    httpd.serve_forever()


if __name__ == '__main__':
    try:
        run()
    except ISC.CC.SessionError as se:
        print("[cmd-ctrld] Error creating cmd-ctrld, "
                "is the command channel daemon running?")        
    except KeyboardInterrupt:
        print("exit http server")
        

