#include "globalVar.h"

char local_ip[INET_ADDRSTRLEN];
char dns_server_ssid[256];
char dns_server_bssid[256];
int http_server_running = 0;
int http_server_preConnected = 0; // Alert that we already have the BSSID

int start_http_server(void){
	int err;
	char command[512];

	printf("HTTP Sever Starting\n");
	if(http_server_preConnected == 0){
		snprintf(command, sizeof(command), "nmcli device wifi list && sleep 1 && nmcli device wifi connect %s bssid %s && sleep 2 && hostname -I > %s", dns_server_ssid, dns_server_bssid, HOST_PORT);
		err = system(command);
		if(err != ZAIRE_OK)return ZAIRE_FAIL;
	}

	snprintf(command, sizeof(command),
		"python3 -m http.server 8801 --directory %s > /dev/null 2>&1 &", HTTP_FOLDER_PATH);

	err = system(command);
	if(err != ZAIRE_OK)return ZAIRE_FAIL;
	http_server_running = 1; // Open
	http_server_preConnected = 1;

}

int stop_http_server(void){
	int err;
	char command[512];
	snprintf(command, sizeof(command), "lsof -t -i:8801 | xargs kill > /dev/null 2>&1 &");
	err = system(command);
	if(err != ZAIRE_OK)return ZAIRE_FAIL;


//	snprintf(command, sizeof(command), "nmcli device disconnect wlan0 > /dev/null && sleep 1");
//	err = system(command);
//	if(err != ZAIRE_OK)return ZAIRE_FAIL;

	//snprintf(command, sizeof(command), "nmcli radio wifi off > /dev/null && sleep 1");
	//err = system(command);
	printf("HTTP Sever Stopped\n");
	http_server_running = 0; // Close

}
void get_local_ip(void){

	int buffer_len = sizeof(local_ip);

	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0){
		perror("socket failed");
		strncpy(local_ip, "127.0.0.1", buffer_len);
		return;
	}

	struct sockaddr_in dummy_addr;
	memset(&dummy_addr, 0, sizeof(dummy_addr));
	dummy_addr.sin_family = AF_INET;
	dummy_addr.sin_port = htons(80);
	inet_pton(AF_INET, "8.8.8.8", &dummy_addr.sin_addr);

	if(connect(sock, (struct sockaddr *)&dummy_addr, sizeof(dummy_addr)) < 0){
		perror("connect failed");
		strncpy(local_ip, "127.0.0.1", buffer_len);
		close(sock);
		return;
	}

	struct sockaddr_in local_addr;
	socklen_t addr_len = sizeof(local_addr);
	if(getsockname(sock, (struct sockaddr *)&local_addr, &addr_len) == -1){
		perror("getsockname failed");
		strncpy(local_ip, "127.0.0.1", buffer_len);
		close(sock);
		return;
	}

	inet_ntop(AF_INET, &local_addr.sin_addr, local_ip, buffer_len);
	close(sock);

}

void get_dns_ssid_bssid(char* id){
	char point[3][256];
	int length= strlen(id);
	int count=0;
	int subject=0;// 0 - H
		     // 1 - SSID
		     // 2 - BSSID
	for(int i = 0; i < length; i++){

		if(id[i] != '|'){

			point[subject][count] = id[i];
			count +=1;
		}else{
			subject +=1;
			count = 0;
		}
	}

	snprintf(dns_server_ssid, sizeof(dns_server_ssid), point[1]);

	if(http_server_preConnected == 0){ //check if we already have BSSID
		snprintf(dns_server_bssid, sizeof(dns_server_bssid), point[2]);
	}

	printf("ID: %s\nMAC: %s\n", dns_server_ssid, dns_server_bssid);

}
