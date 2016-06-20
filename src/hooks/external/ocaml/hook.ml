(* Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC") *)
(* *)
(* This Source Code Form is subject to the terms of the Mozilla Public *)
(* License, v. 2.0. If a copy of the MPL was not distributed with this *)
(* file, You can obtain one at http://mozilla.org/MPL/2.0/. *)

(* Kea option *)

let print_enter n =
    print_string "enter "; print_string n; print_newline()

let print_leave n =
    print_string "leave "; print_string n; print_newline()

let _ = print_enter "opt"

type opt

module Option = struct
    external factory : int -> int -> bytes -> opt = "opt_factory"

    external toText : opt -> string = "opt_toText"

    external getUniverse : opt -> int = "opt_getUniverse"

    external toBinary : opt -> bytes = "opt_toBinary"

    external getType : opt -> int = "opt_getType"

    external len : opt -> int = "opt_len"

    external getHeaderLen : opt -> int = "opt_getHeaderLen"

    external addOption : opt -> opt -> unit = "opt_addOption"

    external getOption : opt -> int -> opt option = "opt_getOption"

    (* TODO: external getOptions : opt -> opt list *)

    external delOption : opt -> int -> bool = "opt_delOption"

    external setData : opt -> bytes -> unit = "opt_setData"

    external setEncapsulatedSpace : opt -> string -> unit =
        "opt_setEncapsulatedSpace"

    external getEncapsulatedSpace : opt -> string =
        "opt_getEncapsulatedSpace"
end

let _ = print_leave "opt"

(* Kea DHCPv4 packet *)

let _ = print_enter "pk4"

type pkt4

module Packet4 = struct
    external toText : pkt4 -> string = "pkt4_toText"

    external addOption : pkt4 -> opt -> unit = "pkt4_addOption"

    external delOption : pkt4 -> int -> bool = "pkt4_delOption"

    external len : pkt4 -> int = "pkt4_len"

    external getType : pkt4 -> int = "pkt4_getType"

    external setType : pkt4 -> int -> unit = "pkt4_setType"

    external setTransid : pkt4 -> int -> unit = "pkt4_setTransid"

    external getTransid : pkt4 -> int = "pkt4_getTransid"

    external inClass : pkt4 -> string -> bool = "pkt4_inClass"

    external addClass : pkt4 -> string -> unit = "pkt4_addClass"

    external getOption : pkt4 -> int -> opt option = "pkt4_getOption"

    external setIndex : pkt4 -> int -> unit = "pkt4_setIndex"

    external getIndex : pkt4 -> int = "pkt4_getIndex"

    external getIface : pkt4 -> string = "pkt4_getIface"

    external setIface : pkt4 -> string -> unit = "pkt4_setIface"
end

let _ = print_leave "pkt4"

(* Kea hook body *)

let _ = print_enter "hook body"

let next_step_continue = 0
let next_step_skip = 1
let next_step_drop = 2

let pkt4_receive query4 =
    print_string "pkt4_receive: handler is called with ";
    print_string (Packet4.toText query4);
    print_newline();
    next_step_continue

let _ = Callback.register "pkt4_receive" pkt4_receive

let _ = print_leave "hook body"
