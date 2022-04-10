/**
 * @file utils.cpp
 * @author Daniel Miranda (danielmirandatm@gmail.com)
 * @brief Implementacao das funcoes utilitarias
 * @version 0.1
 * @date 2022-04-06
 */

#include <utils.hpp>
#include <netdb.h>
#include <stdexcept>


/**
 * @brief Retorna o endereco IP resolvido a partir do endereco de destino escolhido
 * 
 * @param dst_address endereco de destino escolhido pelo usuario
 * @return in_addr_t 
 */
in_addr_t get_ip_by_hostname(const char *dst_address)
{
    struct hostent *host;

    host = gethostbyname(dst_address);
    if (host == 0)
    {
        throw std::runtime_error("Endereco de destino desconhecido");
    }
    
    return *(in_addr_t *)host->h_addr;
}