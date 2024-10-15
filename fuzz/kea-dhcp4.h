#include <string>

extern std::string KEA_DHCP4_CONF = R"(
{
  "Dhcp4": {
    "interfaces-config": {
      "interfaces": [
        "*"
      ]
    },
    "subnet4": [
      {
        "id": 1,
        "pools": [
          {
            "pool": "127.0.0.0/8"
          }
        ],
        "subnet": "127.0.0.0/8"
      }
    ]
  }
}
)";
