/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Client\Client.h"
#include "Framework\Keyboard.h"
#include "Framework\Mouse.h"
#include "GameState\GameState.h"
#include "Framework\Log.h"
#include "Framework\Graphics.h"
#include "Framework\TextSurface.h"
#include "UI\GUIManager.h"

class Game
{
public:
	Game( class MainWindow& wnd,unsigned int width , unsigned int height);
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
public :
	// NOTE: (reductor) std::unique_ptr is only movable, the && is unnecessary
	void SetGameState(std::unique_ptr<GameState>&& newstate);
	Client* GetClient();
	GUIManager* GetGUI();
	// NOTE: (reductor) This appears to be unused
	std::unique_ptr<GameState>& GetState() { return pCurrentState; }
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables        */
	GUIManager GUI;
	Client GameClient;
	std::unique_ptr<GameState> pCurrentState;
	/********************************/
};