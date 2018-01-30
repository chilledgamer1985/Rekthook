

#include "ESP.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "nosmoke.h"
#include "string.h"


void CEsp::Init()
{
	BombCarrier = nullptr;
}

// Yeah dude we're defo gunna do some sick moves for the esp yeah
void CEsp::Move(CUserCmd *pCmd,bool &bSendPacket) 
{

}

// Main ESP Drawing loop
void CEsp::Draw()
{

	IClientEntity *pLocal = hackManager.pLocal();

	if (Menu::Window.VisualsTab.FiltersDead.GetState())
	{
		if (pLocal->IsAlive())
		{
			//Nothing :)
		}
		else
		{
			// Loop through all active entitys
			for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
			{
				// Get the entity
				IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
				player_info_t pinfo;

				// The entity isn't some laggy peice of shit or something
				if (pEntity &&  pEntity != pLocal && !pEntity->IsDormant())
				{
					// Radar
					if (Menu::Window.VisualsTab.OtherRadar.GetState())
					{
						DWORD m_bSpotted = NetVar.GetNetVar(0x839EB159);
						*(char*)((DWORD)(pEntity)+m_bSpotted) = 1;
					}

					// Is it a player?!
					if (Menu::Window.VisualsTab.FiltersPlayers.GetState() && Interfaces::Engine->GetPlayerInfo(i, &pinfo) && pEntity->IsAlive())
					{
						DrawPlayer(pEntity, pinfo);
					}

					// ~ Other ESP's here (items and shit) ~ //
					ClientClass* cClass = (ClientClass*)pEntity->GetClientClass();

					// Dropped weapons
					if (Menu::Window.VisualsTab.FiltersWeapons.GetState() && cClass->m_ClassID != (int)CSGOClassID::CBaseWeaponWorldModel && ((strstr(cClass->m_pNetworkName, "Weapon") || cClass->m_ClassID == (int)CSGOClassID::CDEagle || cClass->m_ClassID == (int)CSGOClassID::CAK47)))
					{
						DrawDrop(pEntity, cClass);
					}

					// If entity is the bomb
					if (Menu::Window.VisualsTab.FiltersC4.GetState())
					{
						if (cClass->m_ClassID == (int)CSGOClassID::CPlantedC4)
							DrawBombPlanted(pEntity, cClass);

						if (cClass->m_ClassID == (int)CSGOClassID::CC4)
							DrawBomb(pEntity, cClass);
					}

					// If entity is a chicken
					if (Menu::Window.VisualsTab.FiltersChickens.GetState())
					{
						if (cClass->m_ClassID == (int)CSGOClassID::CChicken)
							DrawChicken(pEntity, cClass);
					}
				}
			}
		}
	}
	else
	{
		// Loop through all active entitys
		for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
		{
			// Get the entity
			IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
			player_info_t pinfo;

			// The entity isn't some laggy peice of shit or something
			if (pEntity &&  pEntity != pLocal && !pEntity->IsDormant())
			{
				// Radar
				if (Menu::Window.VisualsTab.OtherRadar.GetState())
				{
					DWORD m_bSpotted = NetVar.GetNetVar(0x839EB159);
					*(char*)((DWORD)(pEntity)+m_bSpotted) = 1;
				}

				// Is it a player?!
				if (Menu::Window.VisualsTab.FiltersPlayers.GetState() && Interfaces::Engine->GetPlayerInfo(i, &pinfo) && pEntity->IsAlive())
				{
					DrawPlayer(pEntity, pinfo);
				}

				// ~ Other ESP's here (items and shit) ~ //
				ClientClass* cClass = (ClientClass*)pEntity->GetClientClass();

				// Dropped weapons
				if (Menu::Window.VisualsTab.FiltersWeapons.GetState() && cClass->m_ClassID != (int)CSGOClassID::CBaseWeaponWorldModel && ((strstr(cClass->m_pNetworkName, "Weapon") || cClass->m_ClassID == (int)CSGOClassID::CDEagle || cClass->m_ClassID == (int)CSGOClassID::CAK47)))
				{
					DrawDrop(pEntity, cClass);
				}

				// If entity is the bomb
				if (Menu::Window.VisualsTab.FiltersC4.GetState())
				{
					if (cClass->m_ClassID == (int)CSGOClassID::CPlantedC4)
						DrawBombPlanted(pEntity, cClass);

					if (cClass->m_ClassID == (int)CSGOClassID::CC4)
						DrawBomb(pEntity, cClass);
				}

				// If entity is a chicken
				if (Menu::Window.VisualsTab.FiltersChickens.GetState())
				{
					if (cClass->m_ClassID == (int)CSGOClassID::CChicken)
						DrawChicken(pEntity, cClass);
				}

				//DrawGrenades(pEntity);

			}
		}
	}

	//Those are good like this, no edit needed :)
	if (Menu::Window.MiscTab.OtherSpectators.GetState())
	{
		SpecList();
	}
	// Anti Flash
	if (Menu::Window.VisualsTab.OtherNoFlash.GetState())
	{
		DWORD m_flFlashMaxAlpha = NetVar.GetNetVar(0xFE79FB98);
		*(float*)((DWORD)pLocal + m_flFlashMaxAlpha) = Menu::Window.VisualsTab.OtherNoFlashVal.GetValue();
	}
}

void CEsp::NoSky()
{
	
}
void CEsp::DoFOV()
{
	float FoV;
	std::vector<int> HitBoxesToScan;
	IClientEntity* pLocal = hackManager.pLocal();
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (!pWeapon)
		return;

	if (GameUtils::IsPistol(pWeapon))
	{
		FoV = Menu::Window.LegitBotTab.WeaponPistFoV.GetValue();
		
	}
	else if (GameUtils::IsSniper(pWeapon))
	{
		FoV = Menu::Window.LegitBotTab.WeaponSnipFoV.GetValue();
		
	}
	else
	{
		FoV = Menu::Window.LegitBotTab.WeaponMainFoV.GetValue();
	}
	


	int w, h;
	Interfaces::Engine->GetScreenSize(w, h);
	float CenterX = (float)w / 2;
	float CenterY = (float)h / 2;

	
	Offsets::VMT::Surface_DrawOutlinedCircle;//(CenterX, CenterY, FoV, 360, 0, 255, 0, 255); //(int x, int y, int radius, int segments, int r, int g, int b, int a)
}
void CEsp::SpecList()
{

	IClientEntity *pLocal = hackManager.pLocal();

	RECT scrn = Render::GetViewport();
	int AC = 0;


	// Loop through all active entitys
	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		// Get the entity
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		player_info_t pinfo;

		Render::Text(scrn.left, (scrn.bottom / 2 - 16), Color(0, 150, 255, 255), Render::Fonts::ESP, "Spectating me list:");


		// The entity isn't some laggy peice of shit or something
		if (pEntity &&  pEntity != pLocal)
		{

			if (Interfaces::Engine->GetPlayerInfo(i, &pinfo) && !pEntity->IsAlive() && !pEntity->IsDormant())
			{

				HANDLE obs = pEntity->GetObserverTargetHandle();

				if (obs)
				{
					IClientEntity *pTarget = Interfaces::EntList->GetClientEntityFromHandle(obs);
					player_info_t pinfo2;
					if (pTarget)
					{
						if (Interfaces::Engine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2))
						{
							char buf[255]; sprintf_s(buf, "%s", pinfo.name, pinfo2.name);
							RECT TextSize = Render::GetTextSize(Render::Fonts::ESP, buf);
							//Render::Clear(scrn.left, (scrn.bottom / 3) + (16 * AC), 260, 16, Color(0, 0, 0, 140));
							//Render::Text(scrn.left, (scrn.bottom / 2 - 16), pTarget->GetIndex() == pLocal->GetIndex() ? Color(240, 70, 80, 255) : Color(255, 255, 255, 0), Render::Fonts::ESP, "Spectating me list:");
							Render::Text(scrn.left , (scrn.bottom / 2) + (16 * AC), pTarget->GetIndex() == pLocal->GetIndex() ? Color(240, 70, 80, 255) : Color(255, 255, 255, 0), Render::Fonts::ESP, buf);
							AC++;
						}
					}
				}
			}
		}
	}

	//Render::Outline(scrn.right - 261, (scrn.bottom / 2) - 1, 262, (16 * AC) + 2, Color(23, 23, 23, 255));
	//Render::Outline(scrn.right - 260, (scrn.bottom / 2), 260, (16 * AC), Color(90, 90, 90, 255));
}

//  Yeah m8

//-----------------------------------------------------------------------------
// Purpose: draws the zoom effect
//-----------------------------------------------------------------------------


void CEsp::DrawPlayer(IClientEntity* pEntity, player_info_t pinfo)
{
	//Here is our very advanced system yay

	ESPBox Box;
	Color Color;
	//terrorist red
	int TR = Menu::Window.ColorTab.TVisColorR.GetValue();
	int TNVR = Menu::Window.ColorTab.TNVisColorR.GetValue();
	//terrorist green
	int TG = Menu::Window.ColorTab.TVisColorG.GetValue();
	int TNVG = Menu::Window.ColorTab.TNVisColorG.GetValue();
	//terrorist green
	int TB = Menu::Window.ColorTab.TVisColorB.GetValue();
	int TNVB = Menu::Window.ColorTab.TNVisColorB.GetValue();

	//ct red
	int CTR = Menu::Window.ColorTab.CTVisColorR.GetValue();
	int CTNVR = Menu::Window.ColorTab.CTNVisColorR.GetValue();
	//ct green
	int CTG = Menu::Window.ColorTab.CTVisColorG.GetValue();
	int CTNVG = Menu::Window.ColorTab.CTNVisColorG.GetValue();
	//ct blue
	int CTB = Menu::Window.ColorTab.CTVisColorB.GetValue();
	int CTNVB = Menu::Window.ColorTab.CTNVisColorB.GetValue();


	if (hackManager.pLocal()->IsAlive()) {
		CEsp::DrawLinesAA(Color);
	}
	// Show own team false? well gtfo teammate lol
	if (Menu::Window.VisualsTab.FiltersEnemiesOnly.GetState() && (pEntity->GetTeamNum() == hackManager.pLocal()->GetTeamNum()))
		return;

	if (GetBox(pEntity, Box))
	{
		Color = GetPlayerColor(pEntity);

		if (Menu::Window.VisualsTab.OtherGlow.GetState())
		{
		int TeamNum = pEntity->GetTeamNum();

		if (TeamNum == TEAM_CS_T)
		{

		DrawGlow(pEntity, TNVR, TNVG, TNVB, 255);
		}
		else if (TeamNum == TEAM_CS_CT)
		{
		DrawGlow(pEntity, CTNVR, CTNVG, CTNVB, 255);
		}
		}

		
		

		if (!Menu::Window.VisualsTab.OptionsBox.GetIndex() == 0)
			DrawBox(Box, Color);

		if (Menu::Window.VisualsTab.OptionsName.GetState())
			DrawName(pinfo, Box, pEntity);

		

		if (Menu::Window.VisualsTab.OptionsHealth.GetState())
			DrawHealth2(pEntity, Box);

		if (Menu::Window.VisualsTab.OptionsArmor.GetState())
			DrawArmor(pEntity, Box);

		if (Menu::Window.VisualsTab.OptionsDistance.GetState())
			DrawDistanse(pEntity, Box);

		if (Menu::Window.VisualsTab.OptionsInfo.GetState() || Menu::Window.VisualsTab.OptionsWeapon.GetState())
			DrawInfo(pEntity, Box);

		if (Menu::Window.VisualsTab.OptionsAimSpot.GetState())
			DrawCross(pEntity);

		if (Menu::Window.VisualsTab.OptionsSkeleton.GetState())
			DrawSkeleton(pEntity);

		if (Menu::Window.VisualsTab.OtherGlow.GetState())
		{
			bool IsVis;
			float r;
			float b;
			float g;
			for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
			{
				IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
			}
			if (GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Chest) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Head) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Neck) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::NeckLower) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Pelvis) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Chest) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftFoot) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftHand) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftLowerArm) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftShin) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftThigh) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftUpperArm) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LowerChest) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightFoot) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightHand) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightLowerArm) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightShin) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightThigh) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightUpperArm))
			{
				IsVis = true;
			}
			else
			{
				IsVis = false;
			}

			int TeamNum = pEntity->GetTeamNum();
			if (TeamNum = TEAM_CS_T)
			{
				if (IsVis = true)
				{
					r = Menu::Window.ColorTab.TVisColorR.GetValue();
					g = Menu::Window.ColorTab.TVisColorG.GetValue();
					b = Menu::Window.ColorTab.TVisColorB.GetValue();

				}
				else
				{
					r = Menu::Window.ColorTab.TNVisColorR.GetValue();
				    g = Menu::Window.ColorTab.TNVisColorG.GetValue();
					b = Menu::Window.ColorTab.TNVisColorB.GetValue();

				}
			}
			else
			{
				if (IsVis = true)
				{
					r = Menu::Window.ColorTab.CTVisColorR.GetValue();
					g = Menu::Window.ColorTab.CTVisColorG.GetValue();
					b = Menu::Window.ColorTab.CTVisColorB.GetValue();

				}
				else
				{
					r = Menu::Window.ColorTab.CTNVisColorR.GetValue();
					g = Menu::Window.ColorTab.CTNVisColorG.GetValue();
					b = Menu::Window.ColorTab.CTNVisColorB.GetValue();

				}
			}

			CEsp::DrawGlow(pEntity, r, g, b, 255);

		}
	}
}
void CEsp::DrawDistanse(IClientEntity* pEntity, CEsp::ESPBox size)
{
	IClientEntity *pLocal = hackManager.pLocal();

	Vector vecOrigin = pEntity->GetOrigin();
	Vector vecOriginLocal = pLocal->GetOrigin();
	static RECT defSize = Render::GetTextSize(Render::Fonts::Default, "");

	char dist_to[32];
	sprintf_s(dist_to, "%.0fm", DistanceTo(vecOrigin, vecOriginLocal));

	Render::Text(size.x + size.w + 3, size.y + (0.6*(defSize.bottom + 28)), Color(255, 255, 255, 255), Render::Fonts::ESP, dist_to);
}

float CEsp::DistanceTo(Vector vecDst, Vector vecSrc)
{
	Vector vDelta = vecDst - vecSrc;

	float fDistance = ::sqrtf((vDelta.Length()));

	if (fDistance < 1.0f)
		return 1.0f;

	return fDistance;
}

// glow shit
struct Glowobject
{
	IClientEntity* pEntity;
	Vector Color;
	float Alpha;
	byte PAD[16];
	bool RenderWhenOccluded;
	bool RenderWhenUnOccluded;
	bool FullBloomRender;
	byte PAD2[17];
};
void CEsp::DrawGlow(IClientEntity *pEntity, int r, int g, int b, int a)
{
	static uintptr_t Module = (uintptr_t)GetModuleHandle("client.dll");

	Glowobject* GlowManager = *(Glowobject**)(Module + 0x4FA97F8);

	if (GlowManager)
	{
		Glowobject* GlowObject = &GlowManager[pEntity->GetGlowIndex()];

		if (GlowObject)
		{
			GlowObject->RenderWhenOccluded = 1;
			GlowObject->RenderWhenUnOccluded = 0;

			float glowr = r;
			float glowg = g;
			float glowb = b;
			float glowa = (1);
			GlowObject->Color = Vector(r, g, b);
			GlowObject->Alpha = 255;
		}
	}
}

// Gets the 2D bounding box for the entity
// Returns false on failure nigga don't fail me
bool CEsp::GetBox(IClientEntity* pEntity, CEsp::ESPBox &result)
{
	Vector  vOrigin, min, max, sMin, sMax, sOrigin,
		flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	vOrigin = pEntity->GetOrigin();
	min = pEntity->collisionProperty()->GetMins() + vOrigin;
	max = pEntity->collisionProperty()->GetMaxs() + vOrigin;

	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	if (!Render::WorldToScreen(points[3], flb) || !Render::WorldToScreen(points[5], brt)
		|| !Render::WorldToScreen(points[0], blb) || !Render::WorldToScreen(points[4], frt)
		|| !Render::WorldToScreen(points[2], frb) || !Render::WorldToScreen(points[1], brb)
		|| !Render::WorldToScreen(points[6], blt) || !Render::WorldToScreen(points[7], flt))
		return false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	result.x = left;
	result.y = top;
	result.w = right - left;
	result.h = bottom - top;

	return true;
}

// Get an entities color depending on team and vis ect
Color CEsp::GetPlayerColor(IClientEntity* pEntity)
{
//#define hitboxes (int)CSGOHitboxID::Head, (int)CSGOHitboxID::Neck, (int)CSGOHitboxID::NeckLower, (int)CSGOHitboxID::Stomach, (int)CSGOHitboxID::Pelvis, (int)CSGOHitboxID::UpperChest,(int)CSGOHitboxID::Chest, (int)CSGOHitboxID::LowerChest,(int)CSGOHitboxID::LeftUpperArm, (int)CSGOHitboxID::RightUpperArm, (int)CSGOHitboxID::LeftThigh, (int)CSGOHitboxID::RightThigh, (int)CSGOHitboxID::LeftHand, (int)CSGOHitboxID::RightHand, (int)CSGOHitboxID::LeftFoot, (int)CSGOHitboxID::RightFoot, (int)CSGOHitboxID::LeftShin, (int)CSGOHitboxID::RightShin, (int)CSGOHitboxID::LeftLowerArm, (int)CSGOHitboxID::RightLowerArm
	int TeamNum = pEntity->GetTeamNum();
	bool IsVis;
	if (GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Chest) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Head) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Neck) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::NeckLower) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Pelvis) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Chest) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftFoot) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftHand) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftLowerArm) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftShin) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftThigh) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LeftUpperArm) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::LowerChest) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightFoot) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightHand) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightLowerArm) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightShin) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightThigh) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::RightUpperArm))
	{
		IsVis = true;
	}
	else
	{
		IsVis = false;
	}
	
	Color color;

	if (TeamNum == TEAM_CS_T)
	{
		if (IsVis)
			color = Color(Menu::Window.ColorTab.TVisColorR.GetValue(), Menu::Window.ColorTab.TVisColorG.GetValue(), Menu::Window.ColorTab.TVisColorB.GetValue(), 255);
		else
		{
			
			color = Color(Menu::Window.ColorTab.TNVisColorR.GetValue(), Menu::Window.ColorTab.TNVisColorG.GetValue(), Menu::Window.ColorTab.TNVisColorB.GetValue(), 255);
			
			
			
		}
		    
	}
	else
	{
		if (IsVis)
			color = Color(Menu::Window.ColorTab.CTVisColorR.GetValue(), Menu::Window.ColorTab.CTVisColorG.GetValue(), Menu::Window.ColorTab.CTVisColorB.GetValue(), 255);
		else
			color = Color(Menu::Window.ColorTab.CTNVisColorR.GetValue(), Menu::Window.ColorTab.CTNVisColorG.GetValue(), Menu::Window.ColorTab.CTNVisColorB.GetValue(), 255);
	}


	return color;
}


void CEsp::DrawLinesAA(Color color) {
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pSkip = hackManager.pLocal();

	// LBY
	AngleVectors(QAngle(0, lineLBY, 0), &forward);
	src3D = hackManager.pLocal()->GetOrigin();
	dst3D = src3D + (forward * 55.f); //replace 50 with the length you want the line to have

	ray.Init(src3D, dst3D);

	Interfaces::Trace->TraceRay(ray, 0, &filter, &tr);

	if (!Render::WorldToScreen(src3D, src) || !Render::WorldToScreen(tr.endpos, dst))
		return;

	Render::Line(src.x, src.y, dst.x, dst.y, Color(210, 105, 30, 255));
	// REAL AGNEL
	AngleVectors(QAngle(0, lineRealAngle, 0), &forward);
	dst3D = src3D + (forward * 50.f); //replace 50 with the length you want the line to have

	ray.Init(src3D, dst3D);

	Interfaces::Trace->TraceRay(ray, 0, &filter, &tr);

	if (!Render::WorldToScreen(src3D, src) || !Render::WorldToScreen(tr.endpos, dst))
		return;

	Render::Line(src.x, src.y, dst.x, dst.y, Color(0, 255, 0, 255));

	// Fake AGNEL
	AngleVectors(QAngle(0, lineFakeAngle, 0), &forward);
	dst3D = src3D + (forward * 50.f); //replace 50 with the length you want the line to have

	ray.Init(src3D, dst3D);

	Interfaces::Trace->TraceRay(ray, 0, &filter, &tr);

	if (!Render::WorldToScreen(src3D, src) || !Render::WorldToScreen(tr.endpos, dst))
		return;

	Render::Line(src.x, src.y, dst.x, dst.y, Color(255, 0, 0, 255));
}

// 2D  Esp box
void CEsp::DrawBox(CEsp::ESPBox size, Color color)
{
	if (Menu::Window.VisualsTab.OptionsBoxFill.GetState())
	{
		//Render::Clear(size.x, size.y, size.w, size.h, color);
		if (!Menu::Window.VisualsTab.OptionsBoxFillColor.GetState())
		{
			Render::Clear(size.x - 1, size.y - 1, size.w + 2, size.h + 2, Color(10, 10, 10, 100));
			Render::Clear(size.x + 1, size.y + 1, size.w - 2, size.h - 2, Color(10, 10, 10, 100));
		}
		else
		{
			Render::Clear(size.x - 1, size.y - 1, size.w + 2, size.h + 2, Color(10, 10, 10, 150));
			Render::Clear(size.x + 1, size.y + 1, size.w - 2, size.h - 2, Color(10, 10, 10, 150));
		}
	}
	//if (PlayerBoxes->GetStringIndex() == 1)
	//{
		// Full Box
	//Render::Clear(size.x, size.y, size.w, size.h, color);
	//Render::Clear(size.x - 1, size.y - 1, size.w + 2, size.h + 2, Color(10, 10, 10, 150)); 
	//Render::Clear(size.x + 1, size.y + 1, size.w - 2, size.h - 2, Color(10, 10, 10, 150));
	//}
	//else
	{
		int VertLine;
		int HorzLine;
		// Corner Box
		//bool IsVis = GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Chest);  da dream
		int xd = Menu::Window.VisualsTab.OptionsBox.GetIndex();
		if (Menu::Window.VisualsTab.OptionsBox.GetIndex() == 1)
		{
			VertLine = (((float)size.w) * (0.2f));
			HorzLine = (((float)size.h) * (0.2f));
		}
		if (Menu::Window.VisualsTab.OptionsBox.GetIndex() == 2)
		{
			VertLine = (((float)size.w) * (1.0f));
			HorzLine = (((float)size.h) * (1.0f));
		}

		Render::Clear(size.x, size.y - 1, VertLine, 1, Color(10, 10, 10, 150));
		Render::Clear(size.x + size.w - VertLine, size.y - 1, VertLine, 1, Color(10, 10, 10, 150));
		Render::Clear(size.x, size.y + size.h - 1, VertLine, 1, Color(10, 10, 10, 150));
		Render::Clear(size.x + size.w - VertLine, size.y + size.h - 1, VertLine, 1, Color(10, 10, 10, 150));

		Render::Clear(size.x - 1, size.y, 1, HorzLine, Color(10, 10, 10, 150));
		Render::Clear(size.x - 1, size.y + size.h - HorzLine, 1, HorzLine, Color(10, 10, 10, 150));
		Render::Clear(size.x + size.w - 1, size.y, 1, HorzLine, Color(10, 10, 10, 150));
		Render::Clear(size.x + size.w - 1, size.y + size.h - HorzLine, 1, HorzLine, Color(10, 10, 10, 150));

		Render::Clear(size.x, size.y, VertLine, 1, color);
		Render::Clear(size.x + size.w - VertLine, size.y, VertLine, 1, color);
		Render::Clear(size.x, size.y + size.h, VertLine, 1, color);
		Render::Clear(size.x + size.w - VertLine, size.y + size.h, VertLine, 1, color);

		Render::Clear(size.x, size.y, 1, HorzLine, color);
		Render::Clear(size.x, size.y + size.h - HorzLine, 1, HorzLine, color);
		Render::Clear(size.x + size.w, size.y, 1, HorzLine, color);
		Render::Clear(size.x + size.w, size.y + size.h - HorzLine, 1, HorzLine, color);

	//	Color color23(0, 0, 0);
		
	//	Render::Clear(size.x + size.y ,size.w, size.h, Color(0,0,0,40));
	}


	

}


// Unicode Conversions
static wchar_t* CharToWideChar(const char* text)
{
	size_t size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs_s(NULL, wa, size/4, text, size);
	return wa;
}
void CEsp::DrawArmor(IClientEntity* pEntity, CEsp::ESPBox size)
{
	ESPBox ArmorBar = size;
	ArmorBar.y += (ArmorBar.h + 6);
	ArmorBar.h = 4;

	float ArmorValue = pEntity->ArmorValue();
	float ArmorPerc = ArmorValue / 100.f;
	float Width = (size.w * ArmorPerc);
	ArmorBar.w = Width;

	int armor = pEntity->ArmorValue();

	if (armor > 100)
		armor = 100;
	/* I dont want a change yellow is good */
	//int r = 255 - armor * 2.55;
	//int g = armor * 2.55;

	int armorBar = size.h / 100 * armor;
	int armorBarDelta = size.h - armorBar;

	if (!armor < 1)
	{
		Render::Clear(size.x - 10, size.y - 1, 2, size.h + 2, Color(0, 0, 0, 150));
		Render::Clear(size.x - 9, size.y + 1, 1, size.h * 0.01 * armor, Color(0, 150, 255, 255));
	}
}


// Player name
void CEsp::DrawName(player_info_t pinfo, CEsp::ESPBox size, IClientEntity* pEntity)
{

	RECT nameSize = Render::GetTextSize(Render::Fonts::ESP, pinfo.name);
	if (strlen(pinfo.name) > 16)
	{
		pinfo.name[16] = 0;
		strcat(pinfo.name, "...");
		puts(pinfo.name);
		RECT nameSize = Render::GetTextSize(Render::Fonts::ESP, pinfo.name);
		Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 16, Color(255, 255, 255, 255), Render::Fonts::ESP, pinfo.name);
	}
	else
	{
		RECT nameSize = Render::GetTextSize(Render::Fonts::ESP, pinfo.name);
		Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 16, Color(255, 255, 255, 255), Render::Fonts::ESP, pinfo.name);
	}
	if (Menu::Window.VisualsTab.OptionsHealth.GetState())
	{
		float HealthValue = pEntity->GetHealth();
		float HealthPerc = HealthValue / 100.f;
		//char faszommeretejobbra_cmbe[64];
		//sprintf_s(faszommeretejobbra_cmbe, "HP: %f", HealthPerc);
		//Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 32, Color(255, 255, 255, 255), Render::Fonts::ESP, faszommeretejobbra_cmbe);




		if (autowalldmgtest[pEntity->GetIndex()] != 0) {
			char asasaasasas[64];
			sprintf_s(asasaasasas, "DMG: %f", autowalldmgtest[pEntity->GetIndex()]);
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y + 32, Color(249, 151, 54, 255), Render::Fonts::ESP, asasaasasas);
		}
		else {
			char asasaasasas[64];
			sprintf_s(asasaasasas, "DMG");
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y + 32, Color(255, 0, 0, 200), Render::Fonts::ESP, asasaasasas);
		}
		
		//char sdsdsdsd[64];
		//sprintf_s(sdsdsdsd, "Missed Shots: %i Index: %i", missedLogHits[pEntity->GetIndex()] , pEntity->GetIndex());
		//Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y + 16, Color(255, 0, 0, 255), Render::Fonts::ESP, sdsdsdsd);

		//char sdsdsddddsd[64];
		//sprintf_s(sdsdsddddsd, "EnemyIndex: %i", pEntity->GetIndex());
		//Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 16, Color(255, 0, 0, 255), Render::Fonts::ESP, sdsdsddddsd);

		
		if (ResolverStage[pEntity->GetIndex()] == 1) {
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 32, Color(0, 0, 255, 255), Render::Fonts::ESP, "R::Moving");
		}
		else if (ResolverStage[pEntity->GetIndex()] == 2) {
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 32, Color(0, 230, 0, 255), Render::Fonts::ESP, "R::Lby Prediction");
		}
		else if (ResolverStage[pEntity->GetIndex()] == 3) {
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 32, Color(255, 0, 0, 255), Render::Fonts::ESP, "R::OldLBY+Delta");
		}
		else if (ResolverStage[pEntity->GetIndex()] == 4){
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 32, Color(0, 12, 255, 255), Render::Fonts::ESP, "R::LBYTIMING");
		}
		else if (ResolverStage[pEntity->GetIndex()] == 5) {
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 32, Color(0, 255, 0, 255), Render::Fonts::ESP, "R::Database");
		}
		else if (ResolverStage[pEntity->GetIndex()] == 6) {
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 32, Color(0, 255, 0, 255), Render::Fonts::ESP, "R::Aimbot");
		}
		else if (ResolverStage[pEntity->GetIndex()] == 7) {
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 32, Color(0, 255, 0, 255), Render::Fonts::ESP, "R::AntiAim");
		}
		else {
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 32, Color(237, 140, 16, 255), Render::Fonts::ESP, "Resolver: NotActive");
		} 


	}

}


void CEsp::DrawGrenades(IClientEntity* pEntity)
{


	Vector vGrenadePos2D = Vector(0.f, 0.f, 0.f);
	Vector vGrenadePos3D = Vector(0.f, 0.f, 0.f);
	float fGrenadeModelSize = 0.0f;
	Color colGrenadeColor = Color(0, 0, 0, 0);
	const model_t *model = pEntity->GetModel();

	if (pEntity->GetClientClass())
	{
		if (model)
		{
			studiohdr_t* hdr = Interfaces::ModelInfo->GetStudiomodel(model);
			if (hdr)
			{
				std::string hdrName = hdr->name;
				if (hdrName.find("thrown") != std::string::npos)
				{
					vGrenadePos3D = pEntity->GetOrigin();
					fGrenadeModelSize = hdr->hull_max.DistTo(hdr->hull_min);

					if (!Render::WorldToScreen(vGrenadePos3D, vGrenadePos2D))
						return;

					if (hdrName.find("flash") != std::string::npos)
					{
						//Warning color
						colGrenadeColor = Color(0, 0, 200, 255);
					}
					else if (hdrName.find("incendiarygrenade") != std::string::npos || hdrName.find("molotov") != std::string::npos || hdrName.find("fraggrenade") != std::string::npos)
					{
						//Dangerous color
						colGrenadeColor = Color(200, 0, 0, 255);
					}

					else if (hdrName.find("smoke") != std::string::npos || hdrName.find("decoy") != std::string::npos)
					{
						//Peaceful color
						colGrenadeColor = Color(0, 200, 0, 255);
					}
					//DrawOutlinedCircleGranade(static_cast<int>(vGrenadePos2D.x), static_cast<int>(vGrenadePos2D.y), static_cast<int>(fGrenadeModelSize), colGrenadeColor);
				}
			}
		}
	}
}


// Draw a health bar. For Tf2 when a bar is bigger than max health a second bar is displayed
void CEsp::DrawHealth(IClientEntity* pEntity, CEsp::ESPBox size)
{
	ESPBox HealthBar = size;
	HealthBar.y += (HealthBar.h + 6);
	HealthBar.h = 4;

	float HealthValue = pEntity->GetHealth();
	float HealthPerc = HealthValue / 100.f;
	float Width = (size.w * HealthPerc);
	HealthBar.w = Width;

	// --  Main Bar -- //

	Vertex_t Verts[4];
	Verts[0].Init(Vector2D(HealthBar.x, HealthBar.y));
	Verts[1].Init(Vector2D(HealthBar.x + size.w, HealthBar.y));
	Verts[2].Init(Vector2D(HealthBar.x + size.w, HealthBar.y + 5));
	Verts[3].Init(Vector2D(HealthBar.x, HealthBar.y + 5));

	// Verts[1].Init(Vector2D(HealthBar.x + size.w + 5, HealthBar.y));
	//Verts[2].Init(Vector2D(HealthBar.x + size.w, HealthBar.y + 5));
	//Verts[3].Init(Vector2D(HealthBar.x - 5, HealthBar.y + 5));
	Render::PolygonOutline(4, Verts, Color(10, 10, 10, 255), Color(255, 255, 255, 170));

	Vertex_t Verts2[4];
	Verts2[0].Init(Vector2D(HealthBar.x, HealthBar.y + 1));
	Verts2[1].Init(Vector2D(HealthBar.x + HealthBar.w, HealthBar.y + 1));
	Verts2[2].Init(Vector2D(HealthBar.x + HealthBar.w, HealthBar.y + 5));
	Verts2[3].Init(Vector2D(HealthBar.x, HealthBar.y + 5));

	/*
	Verts2[1].Init(Vector2D(HealthBar.x + HealthBar.w + 4, HealthBar.y + 1));
	Verts2[2].Init(Vector2D(HealthBar.x + HealthBar.w, HealthBar.y + 5));
	Verts2[3].Init(Vector2D(HealthBar.x - 4, HealthBar.y + 5));
	*/
	
	Color colorxd(0, 255, 0);
	Color colorxd2(255, 255, 0);
	Color colorxd3(255, 119, 0);
	Color colorxd4(255, 0, 0);


	Render::Polygon(4, Verts2, GetPlayerColor(pEntity));




	Verts2[0].Init(Vector2D(HealthBar.x + 1, HealthBar.y + 1));

	Verts2[1].Init(Vector2D(HealthBar.x + HealthBar.w, HealthBar.y + 1));
	Verts2[2].Init(Vector2D(HealthBar.x + HealthBar.w, HealthBar.y + 2));
	Verts2[3].Init(Vector2D(HealthBar.x , HealthBar.y + 2));
	/*Verts2[1].Init(Vector2D(HealthBar.x + HealthBar.w + 2, HealthBar.y + 1));
	Verts2[2].Init(Vector2D(HealthBar.x + HealthBar.w, HealthBar.y + 2));
	Verts2[3].Init(Vector2D(HealthBar.x - 2, HealthBar.y + 2));*/

	Render::Polygon(4, Verts2, Color(255, 255, 255, 40));

}

// Cleans the internal class name up to something human readable and nice
std::string CleanItemName(std::string name)
{
	std::string Name = name;
	// Tidy up the weapon Name
	if (Name[0] == 'C')
		Name.erase(Name.begin());

	// Remove the word Weapon
	auto startOfWeap = Name.find("Weapon");
	if (startOfWeap != std::string::npos)
		Name.erase(Name.begin() + startOfWeap, Name.begin() + startOfWeap + 6);

	return Name;
}

// Anything else: weapons, class state? idk
void CEsp::DrawInfo(IClientEntity* pEntity, CEsp::ESPBox size)
{
	std::vector<std::string> Info;

	// Player Weapon ESP
	IClientEntity* pWeapon = Interfaces::EntList->GetClientEntityFromHandle((HANDLE)pEntity->GetActiveWeaponHandle());
	if (Menu::Window.VisualsTab.OptionsWeapon.GetState() && pWeapon)
	{
		ClientClass* cClass = (ClientClass*)pWeapon->GetClientClass();
		if (cClass)
		{
			// Draw it
			Info.push_back(CleanItemName(cClass->m_pNetworkName));
		}
	}

	// Bomb Carrier
	if (Menu::Window.VisualsTab.OptionsInfo.GetState() && pEntity == BombCarrier)
	{
		Info.push_back("Bomb Carrier");
	}

	// Is Scoped
	if (Menu::Window.VisualsTab.OptionIsScoped.GetState() && pEntity->IsScoped())
	{
		Info.push_back("Is Scoped");
	}
	// Has Defuser
	if (Menu::Window.VisualsTab.OptionDefuser.GetState() && pEntity->HasDefuser())
	{
		Info.push_back("Has Defuser");
	}
	// Defusing
	if (Menu::Window.VisualsTab.OptionIsDefusing.GetState() && pEntity->IsDefusing())
	{
		Info.push_back("Is Defusing");
	}

	static RECT Size = Render::GetTextSize(Render::Fonts::Default, "Hi");
	int i = 0;
	for (auto Text : Info)
	{
		// Render both Weapon and Bomb Carrier
		Render::Text(size.x + size.w + 3, size.y + (i*(Size.bottom + 2)), Color(255, 255, 255, 255), Render::Fonts::ESP, Text.c_str());
		i++;
	}
}

void CEsp::DrawHealth2(IClientEntity* pEntity, CEsp::ESPBox size)
{
	ESPBox HealthBar = size;
	HealthBar.y += (HealthBar.h + 20);
	HealthBar.h = 4;

	float HealthValue = pEntity->GetHealth();
	float HealthPerc = HealthValue / 100.f;
	float Width = (size.w * HealthPerc);
	HealthBar.w = Width;

	int health = pEntity->GetHealth();

	if (health > 100)
		health = 100;

	int r = 255 - health * 2.55;
	int g = health * 2.55;

	int healthBar = size.h / 100 * health;
	int healthBarDelta = size.h - healthBar;

	//int iClampedHealth = pEntity->GetHealth();
	//  if (iClampedHealth >= 100)
	//  iClampedHealth = 100;

	Render::Outline(size.x - 4, size.y + 1, 1, size.h * 0.01 * health, Color(r, g, 0, 255));
	Render::Outline(size.x - 5, size.y - 1, 3, size.h + 2, Color(0, 0, 0, 150));
}

// Little cross on their heads
void CEsp::DrawCross(IClientEntity* pEntity)
{
	Vector cross = pEntity->GetHeadPos(), screen;
	static int Scale = 2;
	if (Render::WorldToScreen(cross, screen))
	{
		Render::Clear(screen.x - Scale, screen.y - (Scale * 2), (Scale * 2), (Scale * 4), Color(20, 20, 20, 160));
		Render::Clear(screen.x - (Scale * 2), screen.y - Scale, (Scale * 4), (Scale * 2), Color(20, 20, 20, 160));
		Render::Clear(screen.x - Scale - 1, screen.y - (Scale * 2) - 1, (Scale * 2) - 2, (Scale * 4) - 2, Color(250, 250, 250, 160));
		Render::Clear(screen.x - (Scale * 2) - 1, screen.y - Scale - 1, (Scale * 4) - 2, (Scale * 2) - 2, Color(250, 250, 250, 160));
	}
}

// Draws a dropped CS:GO Item
void CEsp::DrawDrop(IClientEntity* pEntity, ClientClass* cClass)
{
	Vector Box;
	CBaseCombatWeapon* Weapon = (CBaseCombatWeapon*)pEntity;
	IClientEntity* plr = Interfaces::EntList->GetClientEntityFromHandle((HANDLE)Weapon->GetOwnerHandle());
	if (!plr && Render::WorldToScreen(Weapon->GetOrigin(), Box))
	{
		if (!Menu::Window.VisualsTab.OptionsBox.GetIndex() == 0)
		{
			Render::Outline(Box.x - 2, Box.y - 2, 4, 4, Color(255, 255, 255, 255));
			Render::Outline(Box.x - 3, Box.y - 3, 6, 6, Color(10, 10, 10, 150));
		}

		if (Menu::Window.VisualsTab.OptionsInfo.GetState())
		{
			std::string ItemName = CleanItemName(cClass->m_pNetworkName);
			RECT TextSize = Render::GetTextSize(Render::Fonts::ESP, ItemName.c_str());
			Render::Text(Box.x - (TextSize.right / 2), Box.y - 16, Color(255, 255, 255, 255), Render::Fonts::ESP, ItemName.c_str());
		}
	}
}

// Draws a chicken
void CEsp::DrawChicken(IClientEntity* pEntity, ClientClass* cClass)
{
	ESPBox Box;

	if (GetBox(pEntity, Box))
	{
		player_info_t pinfo; strcpy_s(pinfo.name, "Chicken");
		if (!Menu::Window.VisualsTab.OptionsBox.GetIndex() == 0)
			DrawBox(Box, Color(255,255,255,255));

		if (Menu::Window.VisualsTab.OptionsName.GetState())
			DrawName(pinfo, Box, pEntity);
	}
}

// Draw the planted bomb and timer
void CEsp::DrawBombPlanted(IClientEntity* pEntity, ClientClass* cClass)
{
	// Null it out incase bomb has been dropped or planted
	BombCarrier = nullptr;

	Vector vOrig; Vector vScreen;
	vOrig = pEntity->GetOrigin();
	CCSBomb* Bomb = (CCSBomb*)pEntity;

	if (Render::WorldToScreen(vOrig, vScreen))
	{
		float flBlow = Bomb->GetC4BlowTime();
		float TimeRemaining = flBlow - (Interfaces::Globals->interval_per_tick * hackManager.pLocal()->GetTickBase());
		char buffer[64];
		sprintf(buffer, "Bomb explodes in %.1f", TimeRemaining);
		Render::Text(vScreen.x, vScreen.y, Color(255, 255, 255, 255), Render::Fonts::ESP, buffer);
	}
}
// Draw the bomb if it's dropped, or store the player who's carrying 
void CEsp::DrawBomb(IClientEntity* pEntity, ClientClass* cClass)
{
	// Null it out incase bomb has been dropped or planted
	BombCarrier = nullptr;
	CBaseCombatWeapon *BombWeapon = (CBaseCombatWeapon *)pEntity;
	Vector vOrig; Vector vScreen;
	vOrig = pEntity->GetOrigin();
	bool adopted = true;
	HANDLE parent = BombWeapon->GetOwnerHandle();
	if (parent || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
	{
		IClientEntity* pParentEnt = (Interfaces::EntList->GetClientEntityFromHandle(parent));
		if (pParentEnt && pParentEnt->IsAlive())
		{
			BombCarrier = pParentEnt;
			adopted = false;
		}
	}

	if (adopted)
	{
		if (Render::WorldToScreen(vOrig, vScreen))
		{
			Render::Text(vScreen.x, vScreen.y, Color(112, 230, 20, 255), Render::Fonts::ESP, "Bomb");
		}
	}
}

void DrawBoneArray(int* boneNumbers, int amount, IClientEntity* pEntity, Color color)
{
	Vector LastBoneScreen;
	for (int i = 0; i < amount; i++)
	{
		Vector Bone = pEntity->GetBonePos(boneNumbers[i]);
		Vector BoneScreen;

		if (Render::WorldToScreen(Bone, BoneScreen))
		{
			if (i>0)
			{
				Render::Line(LastBoneScreen.x, LastBoneScreen.y, BoneScreen.x, BoneScreen.y, color);
			}
		}
		LastBoneScreen = BoneScreen;
	}
}

void DrawBoneTest(IClientEntity *pEntity)
{
	for (int i = 0; i < 127; i++)
	{
		Vector BoneLoc = pEntity->GetBonePos(i);
		Vector BoneScreen;
		if (Render::WorldToScreen(BoneLoc, BoneScreen))
		{
			char buf[10];
			_itoa_s(i, buf, 10);
			Render::Text(BoneScreen.x, BoneScreen.y, Color(255, 255, 255, 180), Render::Fonts::ESP, buf);
		}
	}
}

void CEsp::DrawSkeleton(IClientEntity* pEntity)
{
	studiohdr_t* pStudioHdr = Interfaces::ModelInfo->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
		{
			vChild = pEntity->GetBonePos(j);
			vParent = pEntity->GetBonePos(pBone->parent);

			if (Render::WorldToScreen(vParent, sParent) && Render::WorldToScreen(vChild, sChild))
			{
				Render::Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(255,255,255,255));
			}
		}
	}
}