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


#define ICMP_PORT 0

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
    /**
     * @brief Construtor da classe Icmp
     * 
     * @param type tipo da mensagem ICMP que será montada
     * @param code codigo da mensagem ICMP que sera montada
     */
    explicit Icmp(icmp_type type = ECHO_REQUEST, icmp_code code = DEFAULT);

    /**
     * @brief Encoda o cabeçalho ICMP ECHO de acordo com o rfc 792:
     *   0                   1                   2                   3
     *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
     *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     *  |     Type      |     Code      |          Checksum             |
     *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     *  |     Data ...
     *  +-+-+-+-+-
     * 
     * @return std::vector<unsigned char>
     */
    std::vector<unsigned char> encode();

private:
    /**
     * @brief tipo da mensagem ICMP
     */
    icmp_type_t type;

    /**
     * @brief codigo da mensagem ICMP
     */
    icmp_code_t code;

    /**
     * @brief identificador da mensagem ICMP
     */
    unsigned short identifier{};

    /**
     * @brief numero sequencial da mensagem ICMP
     */
    unsigned short seq{};

    /**
     * @brief checksum da mensagem
     */
    unsigned int checksum;

    /**
     * @brief campo de dados da mensagem
     */
    std::vector<unsigned char> data;

    /**
     * @brief Calcula o checksum da mensagem ICMP de acordo com o rfc 792.
     * O checksum é o complemento de 16 bits da soma dos bytes da mensagem,
     * onde inicialmente o valor de checksum é zero e é substituido mais 
     * posteriormente.
     */
    void checksum_update();
};

#endif //__ICMP_HPP__
