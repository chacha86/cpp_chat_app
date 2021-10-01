#include "MyChat.h"
#define MSG_PRINT_POS_X 2
#define MSG_PRINT_POS_Y 3
#define CHAT_INPUT_POS_X 0
#define CHAT_INPUT_POS_Y 16

using namespace MyChat;
using namespace std;

ChatView::ChatView() {
	instantiateChatInputPos();
	instantiateMsgPrintPos();
}

void ChatView::printChatWindow() {
	cout << "#############################################################" << endl;
	cout << "##                    채팅 프로그램 v1                     ##" << endl;
	cout << "#############################################################" << endl;
	cout << "##                                                         ##" << endl;
	cout << "##                                                         ##" << endl;
	cout << "##                                                         ##" << endl;
	cout << "##                                                         ##" << endl;
	cout << "##                                                         ##" << endl;
	cout << "##                                                         ##" << endl;
	cout << "##                                                         ##" << endl;
	cout << "##                                                         ##" << endl;
	cout << "##                                                         ##" << endl;
	cout << "##                                                         ##" << endl;
	cout << "#############################################################" << endl;
	cout << "##                                                         ##" << endl;
	cout << "#############################################################" << endl;
}

void ChatView::gotoxy(COORD pos) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ChatView::setChatDataList(vector<ChatData*> msgList) {
	int rowCount = 0;
	for (ChatData* chatData : msgList) {
		msgPrintPos.Y += rowCount;
		gotoxy(msgPrintPos);
		cout << chatData->msg << endl;
		rowCount++;
		msgPrintPos.Y = MSG_PRINT_POS_Y;
	}
	gotoxy(chatInputPos);
}

void ChatView::paintChatDisplay(vector<ChatData*> msgList) {
	system("cls");
	printChatWindow();
	setChatDataList(msgList);
}

void ChatView::instantiateChatInputPos() {
	chatInputPos.X = CHAT_INPUT_POS_X;
	chatInputPos.Y = CHAT_INPUT_POS_Y;
}

void ChatView::instantiateMsgPrintPos() {
	msgPrintPos.X = MSG_PRINT_POS_X;
	msgPrintPos.Y = MSG_PRINT_POS_Y;
}

void ChatView::moveToChatInputPosX(int x) {
	chatInputPos.X = x;
	gotoxy(chatInputPos);
}
