/**
 * @file icmp.cpp
 * @author Daniel Miranda (danielmirandatm@gmail.com)
 * @brief Implementacao dos metodos da classe Icmp
 * @version 0.1
 * @date 2022-04-06
 */

#include <icmp.hpp>
#include <iostream>


/**
 * @brief Construtor da classe Icmp
 * 
 * @param type tipo da mensagem ICMP que será montada
 * @param code codigo da mensagem ICMP que sera montada
 */
Icmp::Icmp(icmp_type type, icmp_code code) : type(type), 
                                             code(code), 
                                             checksum(0)
{
    this->data = std::vector<unsigned char>(2, 0);
}


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
std::vector<unsigned char> Icmp::encode()
{
    std::vector<unsigned char> icmp_header;
    
    this->checksum_update();
    
    icmp_header.push_back(this->type);
    icmp_header.push_back(this->code);
    icmp_header.push_back(this->checksum >> 8);
    icmp_header.push_back(this->checksum & 0xFF);
    
    for (unsigned char & it : this->data)
    {
        icmp_header.push_back((it >> 8));
        icmp_header.push_back((it & 0xFF));
    }
    
    return icmp_header;
}


/**
 * @brief Calcula o checksum da mensagem ICMP de acordo com o rfc 792.
 * O checksum é o complemento de 16 bits da soma dos bytes da mensagem,
 * onde inicialmente o valor de checksum é zero e é substituido mais 
 * posteriormente.
 */
void Icmp::checksum_update()
{
    unsigned int sum;

    // soma todos os bytes da mensagem
    sum = (this->type << 8) | this->code;
    
    for (unsigned char & it : this->data)
    {
        sum += it;
    }
    
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);

    // complemento da soma
    this->checksum = ~sum;
}