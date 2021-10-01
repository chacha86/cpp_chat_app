#ifndef MY_CHAT
#define MY_CHAT
#include "MySocket.h"

#include <thread>
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>

namespace MyChat {
	typedef struct _ChatData {
		std::string userId;
		const char* msg;
	} ChatData;

	class ChatView {
	private:
		//vector<ChatData*> chatDataList;
		COORD chatInputPos;
		COORD msgPrintPos;
		
		void setChatDataList(std::vector<ChatData*> msgList);
		void printChatWindow();
		void gotoxy(COORD pos);

	public:
		ChatView();
		void paintChatDisplay(std::vector<ChatData*> msgList);
		void instantiateChatInputPos();
		void instantiateMsgPrintPos();
		void moveToChatInputPosX(int x);

	};

	class ChatController {
	private:
		ChatView chatView;
		MySocket::Socket* chatSocket;
		std::vector<ChatData*> msgList;
		std::string chatUserId;
		int recvFlag; // 서버에 메시지가 왔는지를 체크하는 플래그값
		char msgBuffer[100]; // 보낼 메시지 저장 버퍼
		int msgBufferIndex; // 버퍼의 현재 인덱스

		void repaintWhenRecvFromServer();
		void sendToServer();
		std::string convertChatDataToString(std::string user, const char* msg);
		ChatData convertStringToChatData(std::string msg);
		void runRecvBackground();

	public:
		ChatController(std::string userId);
		int joinServer(std::string ip, int port);
		void setRecvFlag(int recvFlag);
		void run();

	};
}

#endif