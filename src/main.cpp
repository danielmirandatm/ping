/**
 * @file main.cpp
 * @author Daniel Miranda (danielmirandatm@gmail.com)
 * @brief Arquivo principal do serviço
 * @version 0.1
 * @date 2022-04-06
 */

#include <iostream>
#include <icmp.hpp>
#include <socket.hpp>
#include <utils.hpp>
#include <chrono>

#define MAX_PARAMETERS 2


int main(int argc, char *argv[])
{
    in_addr_t dst_ip;
    std::array<unsigned char, MAX_SIZE_MSG_TO_RCV> msg_rcvd;
    try
    {
        if (argc > MAX_PARAMETERS)
        {
            throw std::runtime_error("Numero de parâmetros excedido. Execute o comando apenas com o parametro [endereço de destino]");
        }

        dst_ip = get_ip_by_hostname(argv[1]);
        std::unique_ptr<Icmp> icmp = std::make_unique<Icmp>();
        std::unique_ptr<Socket> socket = std::make_unique<Socket>(dst_ip, ICMP_PORT, IPPROTO_ICMP);
        
        // Envia a mensagem ICMP
        auto start_time = std::chrono::steady_clock::now();
        socket->snd_msg(icmp->encode());

        // Recebe a resposta da mensagem ICMP
        msg_rcvd = socket->rcv_msg();
        auto end_time = std::chrono::steady_clock::now();

        // Calcula o a diferenca entre os tempos de envio e recebimento dos pacotes
        std::chrono::duration<double> diff_time = end_time - start_time;

        std::cout << "Mensagem enviada com sucesso, resposta recebida em: " << diff_time.count() << " segundos." << std::endl;
    }
    catch (const std::runtime_error &error)
    {
        std::cout << "Exception: " << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}