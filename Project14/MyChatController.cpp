#include <sstream>
#include "MyChat.h"
#define ENTER 13
#define BACKSPACE 8

using namespace MyChat;
using namespace std;

ChatController::ChatController(string userId) {
	memset(this->msgBuffer, 0, sizeof(msgBuffer));
	this->chatUserId = userId;
	this->msgBufferIndex = 0;
	this->recvFlag = 0;
	chatSocket = NULL;
	chatView.paintChatDisplay(msgList);
}

void ChatController::runRecvBackground() {

	while (true) {
		char* str = new char[100];
		strcpy(str, chatSocket->recv_data());
		ChatData* chatData = new ChatData();
		chatData->msg = str;
		chatData->userId = chatUserId;

		msgList.push_back(chatData);
		recvFlag = 1;
	}
}

void ChatController::run() {
	while (true) {
		if (recvFlag == 1) { // 서버에서 메시지가 왔을 때,
			repaintWhenRecvFromServer();
		}
		if (kbhit()) { // 키보드가 입력됐을 때
			char key = getch(); // 키값을 가져오고

			if (key == ENTER) { // 엔터라면
				sendToServer();
			}
			else if (key == BACKSPACE) {

			}
			else {
				msgBuffer[msgBufferIndex++] = key;
				cout << key;
			}
		}
	}
}

void ChatController::repaintWhenRecvFromServer() {
	// 채팅창 다시 그리기
	chatView.paintChatDisplay(msgList);

	// 입력중이던 채팅 메시지를 다시 그려줌
	for (int i = 0; i < msgBufferIndex; i++) {
		cout << msgBuffer[i];
	}

	// 입력 커서를 index 위치로 바꿈
	chatView.moveToChatInputPosX(msgBufferIndex);

	// 평상시 상태로 바꿈
	recvFlag = 0;
}

string ChatController::convertChatDataToString(string user, const char* msg) {
	string rsMsg;
	rsMsg = rsMsg.append(user);
	rsMsg = rsMsg.append(":");
	rsMsg = rsMsg.append(msg);
	rsMsg = rsMsg.append("\n");

	return rsMsg;
}

ChatData ChatController::convertStringToChatData(string msg) {
	ChatData chatData;

	vector<string> answer;
	stringstream ss(msg);
	string temp;

	while (getline(ss, temp, ':')) {
		answer.push_back(temp);
	}
	
	chatData.userId = answer[0];
	chatData.msg = answer[1].c_str();

	return chatData;
}

int ChatController::joinServer(string ip, int port) {
	if (chatSocket == NULL) {
		chatSocket = new MySocket::Socket(ip.c_str(), port);
		thread* t1 = new thread(&ChatController::runRecvBackground, this); 
		t1->detach();
		return 0;
	}
	return -1;
}

void ChatController::sendToServer() {
	// 메시지 보내기
	string sendMsg = convertChatDataToString(chatUserId, msgBuffer);
	// 메시지를 보냈으므로 채팅창 다시 그리고
	chatSocket->send_data(sendMsg.c_str());

	// 메시지를 보냈으므로 메시지 버퍼 index초기화, 커서의 위치 초기화
	msgBufferIndex = 0;
	chatView.instantiateChatInputPos();
	//chatView.paintChatDisplay(msgList);
	memset(msgBuffer, 0, sizeof(msgBuffer)); // msgBuffer의 내용 비운다.

}

void ChatController::setRecvFlag(int recvFlag) {
	this->recvFlag = recvFlag;
}
