#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ERROR(const char* str)
{
    fprintf(stderr, "%s: %s\n", str, strerror(errno));
    exit(EXIT_FAILURE);
}


void print_as_bytes (unsigned char* buff, ssize_t length)
{
    for (ssize_t i = 0; i < length; i++, buff++)
        printf("%.2x ", *buff);
}


int main()
{
    // Tworzy nowy socket i zwraca handle do niego.
    // AF_INET to typ, który oznacza, że socket ma być na IPv4
    // SOCK_RAW to surowe gniazdo (takie, na jakich mamy to zadanie robić). 
    //Z powodu, że gniazda surowe otrzymują kopie wszystkich danych danego protokołu (IPPROTO_ICMP), 
    //to aby uruchomić ten program musimy używać `sudo`
    // IPPROTO_ICMP oznacza, że ten socket będziemy używać aby wysyłać dane zgodnie z protokołem ICMP
    int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock_fd < 0)
        ERROR("socket error");

    for (;;) {
        // tutaj będzie siedzieć adres IP maszyny co wysłała pakiet oraz port z jakiego wysłała
        struct sockaddr_in sender;
        socklen_t sender_len = sizeof(sender);
        // bufor na CAŁY PAKIET co dostaniemy. Rozmiar to IP_MAXPACKET, bo większych pakietów nie możemy dostać, więc nie będzie buffer overflow :)
        u_int8_t buffer[IP_MAXPACKET];

        // blokujące wywołanie odebrania pakietu.
        // Jak dostaniemy pakiet ("z sock_fd"), to w buforze znajdzie się cały pakiet
        // a w sender znajdą się informacje t.j. aderes IP maszyny wysyłającej pakiet i port z jakiego wysłała
        // za pomocą flag można zmieniać zachowanie tej funkcji
        ssize_t packet_len = recvfrom(sock_fd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
        if (packet_len < 0)
            ERROR("recvfrom error");

        // ta część kodu zamieni nam ciąg bajtów reprezentujący adres IP wysyłającej maszyny na string, który możemy wyprintować
        // AF_INET to znowu typ IPv4
        // cp to adres w pamięci początku ciągu bajtów, który reprezentuje adres IP maszyny wysyłającej pakiet
        // a sender_ip_str to zwykły bufor na adres IP przekonwertowany na string
        char sender_ip_str[20];
        inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
        printf("Received IP packet with ICMP content from: %s\n", sender_ip_str);

        // z headera <netinet/ip.h> dostajemy fajną strukturkę (ip_header), dzięki której nie musimy sami interpretować pakietu, tylko
        // wystarczy, że zrobimy cast raw danych z buffera na tę strukturkę, i już będziemy mogli odczytywać dane jakbyśmy od początku
        // dostali dane w takiej strukturze
        struct ip* ip_header = (struct ip*) buffer; // https://sites.uclouvain.be/SystInfo/usr/include/netinet/ip.h.html  zrobić ctrl+f "ip"
        // self-explanatory - ip_header->ip_hl to długość nagłówka IP w 4-bajtowych słowach,
        // dlatego aby dostać offset na początek nagłówka ICMP mnożymy te długość razy 4
        ssize_t	ip_header_len = 4 * (ssize_t)(ip_header->ip_hl);

        // no tu i poniżej wielkiej filozofii nie ma
        printf("IP header: ");
        print_as_bytes(buffer, ip_header_len);
        printf("\n");

        printf("IP data:   ");
        print_as_bytes(buffer + ip_header_len, packet_len - ip_header_len);
        printf("\n\n");
    }
}