
#include <windows.h>
#include "bytearray.hpp"
#include <vector>
#include "hook.hpp"
#include <iostream>
#include <fstream>
#include "kiero.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")


typedef int(__stdcall* f_send)(SOCKET s, char* buf, int len, int flags);
typedef int(__stdcall* f_recv)(SOCKET s, char* buf, int len, int flags);
typedef void(* f_TfmPacketHandler)(ByteArray* packet);

#define _LOG 0

#ifndef FILE_H
#define FILE_H 1
struct TfmPacketHandlerData
{
	int c, cc;
	f_TfmPacketHandler handler;
};

class TfmPlayer
{
public:
	int playerCode;
	std::string playerName;
	int posX, posY;
	void sendEmote(int emoteId);
};

class TfmObject
{
public:
	int objectId, code, posX, posY, angle, vx, vy, sendAll;
	bool dur;
	void sendDelete();
	void sendAntiGravity();
};

struct TfmMapXmlData
{
	int chesseX, cheeseY;
	int holeX, holeY;
	int cheeseCount, holeCount;
};

#endif

namespace tfm
{
	namespace enums
	{
		enum TfmObjects
		{
			Box = 2
		};

		enum TfmMenuTabs
		{
			Me,
			Players,
			Room,
		};
	}

	namespace menu
	{
		extern HWND windowHandle;
		extern HWND overlayWindow;

		auto render(FLOAT aWidth, FLOAT aHeight) -> VOID;
		void initialize();
		void listenKeyPress();
		HWND getCurrentWindow();
	}

	namespace identifiers
	{
		namespace recv
		{
			static const int MouseMovement[] = { 4, 4 };
			static const int ChatMessage[] = { 6, 6 };
			static const int Crouch[] = { 4, 9 };
			static const int PlaceObject[] = { 5, 20 };
		}

		namespace send
		{
			static const int Emote[] = { 8, 1 };
			static const int ChatMessage[] = { 6, 6 };
			static const int CorrectVersion[] = { 28, 1 };
			static const int DemolitionSkill[] = { 5, 15 };
			static const int EnterHole[] = { 5, 18 };
			static const int GetCheese[] = { 5, 19 };
			static const int Tribulle[] = { 60, 3 };
			static const int ConvertSkill[] = { 5, 14 };
			static const int Map26[] = { 5, 8 };
			static const int IceCube[] = { 5, 21 };
			static const int DefilantePoints[] = { 5, 25 };
			static const int GravitySkill[] = { 5, 28 };
			static const int Ping[] = { 8, 30 };
			static const int Meep[] = { 8, 39 };
			static const int Vampire[] = { 8, 66 };
			static const int AntigravitySkill[] = { 5, 29 };
			static const int Crouch[] = { 4, 9 };
			static const int Login[] = { 26, 8 };
			static const int OldProtocol[] = { 1, 1 };
		}

	}

	namespace variables
	{
		extern bool isTfmOriginal;
		extern ByteArray* packetArr;
		extern bool instantCheese;
		extern bool instantHole;

		namespace menu 
		{
			extern bool showMenu;
			extern enums::TfmMenuTabs selectedTab;
		}
	}

	namespace xml_reader
	{
		TfmMapXmlData readXmlMap(char* xml);
	}

	namespace utils
	{
		#define log( format, ... ) ::printf( "[ TFMMenu ]: " format "\n", ##__VA_ARGS__ )
	}

	namespace room 
	{
		extern int gravityX, gravityY;
		extern int chesseX, cheeseY;
		extern int holeX, holeY;
		extern int roundCode;
		extern std::vector<TfmPlayer*> players;
		extern std::vector<TfmObject*> objects;

		TfmPlayer* getPlayerByName(char* name);
		TfmPlayer* getPlayerByName(std::string name);
		TfmPlayer* getPlayerByCode(int playerCode);
		std::vector<TfmPlayer*> getAllPlayers();

		TfmObject getObjectById(int objectId);
		std::vector<TfmObject*> getObjectsByCode(int code);
		std::vector<TfmObject*> getAllObjects();
		void removeAllObjects();

		void spawnObject(int code, int posX, int posY, int angle, int vx, int vy, bool dur, bool origin, bool send);
		void changeGravity(int velX, int velY);
		void sendIceCube(int playerCode, int posX, int posY);
		void sendBridgeBreak(int bridgeCode);
		void increaseDefilantePoints();

		void sendChatMessage(char* message);

		void sendAllPlayersEmote(int emoteId);
		
	}

	namespace me
	{
		void sendMort(int roundCode);
		void getCheese(int cheeseX, int cheeseY, int distance);
		void enterHole(int holeType, int monde, int distance, int holeX, int holeY);
		void projectionSkill(int posX, int posY, int dir);

		void marryPlayer(char* targetPlayerName);
		void sendCrouch();
		void sendMeep(int posX, int posY);
	}


	namespace hooks 
	{
		int __stdcall hookedSend(SOCKET s, char* buf, int len, int flags);
		int __stdcall hookedRecv(SOCKET s, char* buf, int len, int flags);
	}

	namespace network 
	{
		extern SOCKET socket;
		extern f_send oSend;
		extern f_recv oRecv;
		extern int lastPacketId;

		int sendPacket(ByteArray packet);
		void recvPacket(ByteArray packet);
	}

	namespace packets
	{
		namespace handlers
		{
			namespace send
			{
				extern std::vector<TfmPacketHandlerData> packetHandlers;

				f_TfmPacketHandler getPacketHandler(int c, int cc);
				bool addPacketHandler(int c, int cc, f_TfmPacketHandler handler);
				bool addPacketHandler(const int identifier[], f_TfmPacketHandler handler);

				void handleCorrectVersion(ByteArray* packet);
				void handleLogin(ByteArray* packet);
				void handleOldProtocol(ByteArray* packet);
			}

			namespace recv
			{
				extern std::vector<TfmPacketHandlerData> packetHandlers;
				f_TfmPacketHandler getPacketHandler(int c, int cc);
				bool addPacketHandler(int c, int cc, f_TfmPacketHandler handler);
				bool addPacketHandler(const int identifier[], f_TfmPacketHandler handler);

				void handlePlayerMovement(ByteArray* packet);
				void handlePlayerCrouch(ByteArray* packet);
				void handlePlaceObject(ByteArray* packet);
			}

			void registerHandlers();
		}
	}

	void initialize();


}