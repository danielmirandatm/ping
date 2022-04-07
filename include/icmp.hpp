/**
 * @file icmp.hpp
 * @author Daniel Miranda (danielmirandatm@gmail.com)
 * @brief Header da classe Icmp utilizada para construção
 * de mensagens seguindo o padrão rfc792
 * @version 0.1
 * @date 2022-04-06
 */

#ifndef __ICMP_HPP__
#define __ICMP_HPP__

#include <memory>
#include <vector>

// Tipos de mensagens ICMP do padrao rfc792
typedef enum icmp_type
{
    ECHO_REPLY = 0,
    DESTINATION_UNREACHABLE = 3,
    SOURCE_QUENCH = 4,
    REDIRECT_MESSAGE = 5,
    ECHO_REQUEST = 8,
    ROUTER_ADVERTISEMENT = 9,
    ROUTER_SOLICITATION = 10,
    TIME_EXCEEDED = 11,
    PARAMETER_PROBLEM = 12,
    TIMESTAMP = 13,
    TIMESTAMP_REPLY = 14,
    INFORMATION_REQUEST = 15,
    INFORMATION_REPLY = 16,
    ADDRESS_MASK_REQUEST = 17,
    ADDRESS_MASK_REPLY = 18,
    TRACEROUTE = 30,
    EXTENDED_ECHO_REQUEST = 42,
    EXTENDED_ECHO_REPLY = 19,
} icmp_type_t;

// Códigos de mensagens ICMP do padrao rfc792
typedef enum icmp_code
{
    // case icmp_type = 3
    NETWORK_UNREACHABLE = 0,
    HOST_UNREACHABLE = 1,
    PROTOCOL_UNREACHABLE = 2,
    PORT_UNREACHABLE = 3,
    FRAGMENTATION_NEEDED_AND_DF_SET = 4,
    SOURCE_ROUTE_FAILED = 5,

    // case icmp_type = 5
    REDIRECT_DATAGRAMS_FOR_THE_NETWORK = 0,
    REDIRECT_DATAGRAMS_FOR_THE_HOST = 1,
    REDIRECT_DATAGRAMS_FOR_THE_TYPE_OF_SERVICE_AND_NETWORK = 2,
    REDIRECT_DATAGRAMS_FOR_THE_TYPE_OF_SERVICE_AND_HOST = 3,

    // case icmp_type = 11
    TIME_TO_LIVE_EXCEEDED = 0,
    FRAGMENT_REASSEMBLY_TIME_EXCEEDED = 1,

    // case icmp_type = 0 || 8 || 12 || 4 || 13 || 14 || 15 || 16
    DEFAULT = 0
} icmp_code_t;


class Icmp
{
public:
    Icmp(icmp_type type = ECHO_REQUEST, icmp_code code = DEFAULT);
    std::vector<unsigned char> encode();

private:
    icmp_type_t type;
    icmp_code_t code;
};

#endif //__ICMP_HPP__
