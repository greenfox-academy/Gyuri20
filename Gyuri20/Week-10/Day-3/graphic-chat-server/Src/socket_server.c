/* Includes ------------------------------------------------------------------*/
#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"
#include "stm32746g_discovery_ts.h"
#include <string.h>
#include "stm32746g_discovery_lcd.h"
#define SERVER_QUEUE_SIZE 100
#define SERVER_BUFF_LEN 100

//uint16_t x_y [1];

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void terminate_thread()
{
	while (1)
		osThreadTerminate(NULL);
}
// TODO:
// Implement this function!

void socket_server_thread(void const *argument)
{
		BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
		LCD_UsrLog("Socket server - startup...\n");
		LCD_UsrLog("Socket server - waiting for IP address...\n");

		// Wait for an IP address
		while (!is_ip_ok())
			osDelay(10);
		LCD_UsrLog("Socket server - IP address is ok\n");

		// Create server socket
		int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
		if (server_socket < 0) {
			LCD_ErrLog("Socket server - can't create socket\n");
			terminate_thread();
		}
		LCD_UsrLog("Socket server - socket created\n");

		// Create address structure and bind the socket to it
		struct sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(54545);
		server_addr.sin_addr.s_addr = INADDR_ANY;
		if (bind(server_socket, (struct sockaddr*)&(server_addr), sizeof(server_addr)) < 0) {
			LCD_ErrLog("Socket server - can't bind socket\n");
			terminate_thread();
		}
		LCD_UsrLog("Socket server - socket bind ok\n");

		// Start listening
		if (listen(server_socket, SERVER_QUEUE_SIZE) < 0) {
			LCD_ErrLog("Socket server - can't listen\n");
			terminate_thread();
		}
		LCD_UsrLog("Socket server - listening...\n");

		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);
		int client_socket;
		TS_StateTypeDef TS_State;
		TS_StateTypeDef *TS_State_ptr = &TS_State;
		while (1) {
			// Accept incoming connections
			client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
			LCD_UsrLog("Socket server - connection accepted\n");
			BSP_LCD_Clear(LCD_COLOR_GREEN);
			// Check the client socket
			if (client_socket < 0) {
				LCD_ErrLog("Socket server - invalid client socket\n");
			} else {
				// Define buffer for incoming message
				//char buff[SERVER_BUFF_LEN];
				int received_bytes;
				// Receive data
				do {
					if (BSP_PB_GetState(BUTTON_KEY) == 1) {
						BSP_LCD_Clear(LCD_COLOR_WHITE);
					}

					received_bytes = recv(client_socket, &TS_State, sizeof(TS_State), 0);
					BSP_LCD_FillCircle(TS_State_ptr->touchX[0], TS_State_ptr->touchY[0], 10);
					// Check for error
					/*if (received_bytes < 0) {
						LCD_ErrLog("Socket server - can't receive\n");
					} else {
						// Close the string
						buff[received_bytes] = '\0';

						// Print message
						LCD_UsrLog("Socket server - message:");
						LCD_UsrLog(buff);
						LCD_UsrLog("\n");

						// Send back the message
						send(client_socket, buff, received_bytes, 0);*/
					//}
				} while (received_bytes > 0);

				// Close the socket
				closesocket(client_socket);
				LCD_UsrLog("Socket server - connection closed\n");
			}
		}

		// Close socket
		closesocket(server_socket);

		while (1) {
			osDelay(10);
		}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
