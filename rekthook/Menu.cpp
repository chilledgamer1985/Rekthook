

#include "Menu.h"
#include "Controls.h"
#include "Hooks.h"
#include "Interfaces.h"
#include "CRC32.h"
#include <string>
#include "ItemDefinitions.hpp"
#include "Hooks.h"
#include "Hacks.h"
#include "Chams.h"
#include "ESP.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "MiscHacks.h"
#include "CRC32.h"
#include "Resolver.h"
#include "MiscHacks.h"

#define WINDOW_WIDTH 950
#define WINDOW_HEIGHT 650

rekthookwindow Menu::Window;

void Unloadbk()
{
	DoUnload = true;
}

void NApplyCallbk()
{
	
}
void Memz()
{
//	Hooks::XD3();
}
void SaveCallbk()
{
	switch (Menu::Window.SettingsTab.SetNr.GetIndex())
	{
	case 0:
		GUI.SaveWindowState(&Menu::Window, "legit.xml");
		break;
	case 1:
		GUI.SaveWindowState(&Menu::Window, "semirage.xml");
		break;
	case 2:
		GUI.SaveWindowState(&Menu::Window, "rage.xml");
		break;
	case 3:
		GUI.SaveWindowState(&Menu::Window, "faceit.xml");
		break;
	case 4:
		GUI.SaveWindowState(&Menu::Window, "faceit1.xml");
		break;
	case 5:
		GUI.SaveWindowState(&Menu::Window, "nospread.xml");
		break;
	case 6:
		GUI.SaveWindowState(&Menu::Window, "nospread1.xml");
		break;
	}
	
}

void LoadCallbk()
{
	switch (Menu::Window.SettingsTab.SetNr.GetIndex())
	{
	case 0:
		GUI.LoadWindowState(&Menu::Window, "legit.xml");
		break;
	case 1:
		GUI.LoadWindowState(&Menu::Window, "semirage.xml");
		break;
	case 2:
		GUI.LoadWindowState(&Menu::Window, "rage.xml");
		break;
	case 3:
		GUI.LoadWindowState(&Menu::Window, "faceit.xml");
		break;
	case 4:
		GUI.LoadWindowState(&Menu::Window, "faceit1.xml");
		break;
	case 5:
		GUI.SaveWindowState(&Menu::Window, "nospread.xml");
		break;
	case 6:
		GUI.SaveWindowState(&Menu::Window, "nospread1.xml");
		break;
	}
}

void UnLoadCallbk()
{
	DoUnload = true;
}

void KnifeApplyCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");

}/*void SetAKCB()
{
	IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	IClientEntity* WeaponEnt = Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	CBaseCombatWeapon* Weapon = (CBaseCombatWeapon*)WeaponEnt;
	*Weapon->FallbackPaintKit() = 524;

}*/
void rekthookwindow::Setup()
{
	SetPosition(50, 50);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTitle("rekthook 2.2");

	RegisterTab(&RageBotTab);
	RegisterTab(&LegitBotTab);
	RegisterTab(&VisualsTab);
	RegisterTab(&MiscTab);
	//RegisterTab(&ColorTab);
	RegisterTab(&SettingsTab);
//	RegisterTab(&SkinchangerTab);

	//RECT Client = GetClientArea();
	//Client.bottom -= 29;

	RageBotTab.Setup();
	LegitBotTab.Setup();
	VisualsTab.Setup();
	MiscTab.Setup();
	ColorTab.Setup();
	SettingsTab.Setup();
	//SkinchangerTab.Setup();
}

void CRageBotTab::Setup()
{
	
	SetTitle("RageBot");

	ActiveLabel.SetPosition(16, 16);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(66, 16);
	RegisterControl(&Active);

#pragma region Aimbot

	AimbotGroup.SetPosition(16, 48);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(376, 270);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Enable", this, &AimbotEnable);

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl("Auto Fire", this, &AimbotAutoFire);

	AimbotFov.SetFileId("aim_fov");
	AimbotFov.SetBoundaries(0.f, 180.f);
	AimbotFov.SetValue(180.f);
	AimbotGroup.PlaceLabledControl("FOV Range", this, &AimbotFov);

	AimbotSilentAim.SetFileId("aim_silent");
	AimbotGroup.PlaceLabledControl("Silent Aim", this, &AimbotSilentAim);

	AimbotPerfectSilentAim.SetFileId("aim_psilent");
	AimbotGroup.PlaceLabledControl("Perfect Silent", this, &AimbotPerfectSilentAim);


	AimbotAutoRevolver.SetFileId("aim_autorevolver");
	AimbotGroup.PlaceLabledControl("Auto Revolver", this, &AimbotAutoRevolver);



	AimbotAutoPistol.SetFileId("aim_autopistol");
	AimbotGroup.PlaceLabledControl("Auto Pistol", this, &AimbotAutoPistol);

	

	AimbotAutoPistolD.SetFileId("aim_autopistold");
	AimbotAutoPistolD.SetBoundaries(0.f, 500.f);
	AimbotAutoPistolD.SetValue(0.f);
	AimbotGroup.PlaceLabledControl("Auto Pistol Delay", this, &AimbotAutoPistolD);

	AimbotAimStep.SetFileId("aim_aimstep");
	AimbotGroup.PlaceLabledControl("Aim Step", this, &AimbotAimStep);

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl("On Key Press", this, &AimbotKeyPress);

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl("Key", this, &AimbotKeyBind);

	AimbotStopKey.SetFileId("aim_stop");
	AimbotGroup.PlaceLabledControl("Stop Aim", this, &AimbotStopKey);
#pragma endregion Aimbot Controls Get Setup in here

#pragma region Target
	TargetGroup.SetPosition(16, 334);
	TargetGroup.SetText("Target");
	TargetGroup.SetSize(376, 168);
	RegisterControl(&TargetGroup);

	TargetSelection.SetFileId("tgt_selection");
	TargetSelection.AddItem("FOV");
	TargetSelection.AddItem("Distance");
	TargetSelection.AddItem("Health");
	TargetGroup.PlaceLabledControl("Selection", this, &TargetSelection);

	TargetFriendlyFire.SetFileId("tgt_friendlyfire");
	TargetGroup.PlaceLabledControl("Shot Trought Team", this, &TargetFriendlyFire);

	TargetHitbox.SetFileId("tgt_hitbox");
	TargetHitbox.AddItem("Head");
	TargetHitbox.AddItem("Neck");
	TargetHitbox.AddItem("Chest");
	TargetHitbox.AddItem("Stomach");
	TargetHitbox.AddItem("Foots");
	TargetGroup.PlaceLabledControl("Hitbox", this, &TargetHitbox);

	TargetHitscan.SetFileId("tgt_hitscan");
	TargetHitscan.AddItem("Off");
	TargetHitscan.AddItem("Low");
	TargetHitscan.AddItem("Medium");
	TargetHitscan.AddItem("High");
	TargetGroup.PlaceLabledControl("Hitscan", this, &TargetHitscan);

	TargetMultipoint.SetFileId("tgt_multipoint");
	TargetGroup.PlaceLabledControl("Multipoint", this, &TargetMultipoint);

	TargetPointscale.SetFileId("tgt_pointscale");
	TargetPointscale.SetBoundaries(0.f, 10.f);
	TargetPointscale.SetValue(5.f);
	TargetGroup.PlaceLabledControl("Aim Height", this, &TargetPointscale);
#pragma endregion Targetting controls 

#pragma region Accuracy
	AccuracyGroup.SetPosition(408, 48);
	AccuracyGroup.SetText("Accuracy");
	AccuracyGroup.SetSize(360, 240); //280
	RegisterControl(&AccuracyGroup);

	AccuracyRecoil.SetFileId("acc_norecoil");
	AccuracyGroup.PlaceLabledControl("NoRecoil", this, &AccuracyRecoil);

	AccuracyAutoWall.SetFileId("acc_awall");
	AccuracyGroup.PlaceLabledControl("AutoWall", this, &AccuracyAutoWall);

	AccuracyMinimumDamage.SetFileId("acc_mindmg");
	AccuracyMinimumDamage.SetBoundaries(1.f, 100.f);
	AccuracyMinimumDamage.SetValue(1.f);
	AccuracyGroup.PlaceLabledControl("AutoWall Minimum Damage", this, &AccuracyMinimumDamage);


	AccuracyAutoScope.SetFileId("acc_scope");
	AccuracyGroup.PlaceLabledControl("Auto Scope", this, &AccuracyAutoScope);


	LowerbodyFix.SetFileId("acc_lowerbodyfix");
	AccuracyGroup.PlaceLabledControl("LBY Correction", this, &LowerbodyFix);

	AdvancedResolver.SetFileId("acc_advancedresolver");
	AccuracyGroup.PlaceLabledControl("Pitch Correction", this, &AdvancedResolver);

	AimbotResolver.SetFileId("acc_aaa");
	AimbotResolver.AddItem("Off");
	AimbotResolver.AddItem("Level 1");
	AimbotResolver.AddItem("Level 2");
	AimbotResolver.AddItem("Level 3");
	AccuracyGroup.PlaceLabledControl("Resolver", this, &AimbotResolver);

	AccuracyHitchance.SetFileId("acc_chance");
	AccuracyHitchance.SetBoundaries(0, 100);
	AccuracyHitchance.SetValue(10);
	AccuracyGroup.PlaceLabledControl("Hit Chance", this, &AccuracyHitchance);

	BaimIfUnderXHealth.SetFileId("acc_BaimIfUnderXHealth");
	BaimIfUnderXHealth.SetBoundaries(0, 100);
	BaimIfUnderXHealth.SetValue(0);
	AccuracyGroup.PlaceLabledControl("Body-Aim if HP is lower than X", this, &BaimIfUnderXHealth);


	PreferBodyAim.SetFileId("acc_preferbaim");
	AccuracyGroup.PlaceLabledControl("Prefer Body-Aim", this, &PreferBodyAim);

	AimbotChangeSideAA.SetFileId("changeSideAA");
	AccuracyGroup.PlaceLabledControl("Change Side on Headshot", this, &AimbotChangeSideAA);

	//AimbotTargetSide.SetFileId("switchsideonpress");
	//AccuracyGroup.PlaceLabledControl("Target+180 on Key", this, &AimbotTargetSide);

	//AimbotBaimOnKey.SetFileId("baimonkeypress");
	//AccuracyGroup.PlaceLabledControl("BAIM Key", this, &AimbotBaimOnKey);

	//AimbotKeyFakeWalk.SetFileId("fakwewalkkey");
	//AccuracyGroup.PlaceLabledControl("Fake Walk Key", this, &AimbotKeyFakeWalk);

	//AimbotKeyFakeWalk.SetFileId("fakwewalkkey");
	//AimbotGroup.PlaceLabledControl("Fakewalk Key", this, &AimbotKeyFakeWalk);

	
	//AccuracyResolver.SetFileId("acc_aaa");
	//AccuracyResolver.AddItem("Off");
	//AccuracyResolver.AddItem("Auto Resolver");
	//AccuracyResolver.AddItem("LBY BF");
	//AccuracyGroup.PlaceLabledControl("Anti Aim Resolver", this, &AccuracyResolver);

	//AccuracyPositionAdjustment.SetFileId("acc_posadj");
	//AccuracyGroup.PlaceLabledControl("Position Adjustment", this, &AccuracyPositionAdjustment);

	//AccuracySmart.SetFileId("acc_smart");
	//AccuracySmart.SetBoundaries(0, 20);
	//AccuracySmart.SetValue(0);
	//AccuracyGroup.PlaceLabledControl("Smart Aim", this, &AccuracySmart);
#pragma endregion  Accuracy controls get Setup in here


#pragma region AntiAim
	AntiAimGroup.SetPosition(408, 297);
	AntiAimGroup.SetText("Anti Aim");
	AntiAimGroup.SetSize(360, 270);
	RegisterControl(&AntiAimGroup);

	AntiAimEnable.SetFileId("aa_enable");
	AntiAimGroup.PlaceLabledControl("Enable", this, &AntiAimEnable);

	AntiAimPitch.SetFileId("aa_x");
	AntiAimPitch.AddItem("Off");
	AntiAimPitch.AddItem("Halfdown");
	AntiAimPitch.AddItem("Jitter");
	AntiAimPitch.AddItem("Emotion");
	AntiAimPitch.AddItem("Up");
	AntiAimPitch.AddItem("Zero");
	AntiAimPitch.AddItem("Custom");
	AntiAimGroup.PlaceLabledControl("Pitch", this, &AntiAimPitch);

	AntiAimYaw.SetFileId("aa_y");
	AntiAimYaw.AddItem("Off");
	AntiAimYaw.AddItem("Fast Spin");
	AntiAimYaw.AddItem("Slow Spin");
	AntiAimYaw.AddItem("Jitter");
	AntiAimYaw.AddItem("180 Jitter");
	AntiAimYaw.AddItem("Backwards");
	AntiAimYaw.AddItem("Backwards Jitter");
	AntiAimYaw.AddItem("Sideways Switch");
	AntiAimYaw.AddItem("Sideways Right");
	AntiAimYaw.AddItem("Sideways Left");
	AntiAimYaw.AddItem("LBY");
	AntiAimYaw.AddItem("LBY Jitter");
	AntiAimYaw.AddItem("LBY Sideways");
	AntiAimYaw.AddItem("LBY Spin");
	AntiAimYaw.AddItem("LBY Break");
	AntiAimGroup.PlaceLabledControl("Real Yaw", this, &AntiAimYaw);

	FakeYaw.SetFileId("fakeaa");
	FakeYaw.AddItem("Off");
	FakeYaw.AddItem("Fast Spin");
	FakeYaw.AddItem("Slow Spin");
	FakeYaw.AddItem("Jitter");
	FakeYaw.AddItem("180 Jitter");
	FakeYaw.AddItem("Backwards");
	FakeYaw.AddItem("Backwards Jitter");
	FakeYaw.AddItem("Sideways Switch");
	FakeYaw.AddItem("Sideways Right");
	FakeYaw.AddItem("Sideways Left");
	FakeYaw.AddItem("LBY");
	FakeYaw.AddItem("LBY Jitter");
	FakeYaw.AddItem("LBY Sideways");
	FakeYaw.AddItem("LBY Spin");
	FakeYaw.AddItem("LBY Break");
	AntiAimGroup.PlaceLabledControl("Fake Yaw", this, &FakeYaw);


	AntiAimOffset.SetFileId("aa_offset");
	AntiAimOffset.SetBoundaries(0, 360);
	AntiAimOffset.SetValue(0);
	AntiAimGroup.PlaceLabledControl("Add Real Yaw", this, &AntiAimOffset);




	LBY.SetFileId("aa_lby");
	AntiAimGroup.PlaceLabledControl("Anti Resolver", this, &LBY);

	AntiAimEdge.SetFileId("aa_edge");
	AntiAimGroup.PlaceLabledControl("Wall Detection", this, &AntiAimEdge);

	AntiAimKnife.SetFileId("aa_knife");
	AntiAimGroup.PlaceLabledControl("Knife/Nade Anti Aim", this, &AntiAimKnife);

	AntiAimTarget.SetFileId("aa_target");
	AntiAimGroup.PlaceLabledControl("At Targets", this, &AntiAimTarget);
#pragma endregion  AntiAim controls get setup in here
}

void CLegitBotTab::Setup()
{
	SetTitle("LegitBot");

	ActiveLabel.SetPosition(16, 16);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(66, 16);
	RegisterControl(&Active);

#pragma region Aimbot
	AimbotGroup.SetPosition(16, 48);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(240, 210);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Enable", this, &AimbotEnable);

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl("Auto Fire", this, &AimbotAutoFire);

	AimbotFriendlyFire.SetFileId("aim_friendfire");
	AimbotGroup.PlaceLabledControl("Friendly Fire", this, &AimbotFriendlyFire);

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl("On Key Press", this, &AimbotKeyPress);

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl("Key Bind", this, &AimbotKeyBind);
	
	AimbotAutoPistol.SetFileId("aim_apistol");
	AimbotGroup.PlaceLabledControl("Auto Pistol", this, &AimbotAutoPistol);

#pragma endregion Aimbot shit

#pragma region Triggerbot
	TriggerGroup.SetPosition(272, 48);
	TriggerGroup.SetText("Triggerbot");
	TriggerGroup.SetSize(240, 210);
	RegisterControl(&TriggerGroup);

	TriggerEnable.SetFileId("trig_enable");
	TriggerGroup.PlaceLabledControl("Enable", this, &TriggerEnable);

	TriggerKeyPress.SetFileId("trig_onkey");
	TriggerGroup.PlaceLabledControl("On Key Press", this, &TriggerKeyPress);

	TriggerKeyBind.SetFileId("trig_key");
	TriggerGroup.PlaceLabledControl("Key Bind", this, &TriggerKeyBind);

	TriggerDelay.SetFileId("trig_time");
	TriggerDelay.SetBoundaries(1.f, 1000.f);
	TriggerDelay.SetValue(1.f);
	TriggerGroup.PlaceLabledControl("Delay (ms)", this, &TriggerDelay);

	TriggerRecoil.SetFileId("trig_recoil");
	TriggerGroup.PlaceLabledControl("Recoil", this, &TriggerRecoil);

	TriggerFilterGroup.SetPosition(528, 48);
	TriggerFilterGroup.SetText("Triggerbot Filter");
	TriggerFilterGroup.SetSize(240, 210);
	RegisterControl(&TriggerFilterGroup);

	TriggerHead.SetFileId("trig_head");
	TriggerFilterGroup.PlaceLabledControl("Head", this, &TriggerHead);

	TriggerChest.SetFileId("trig_chest");
	TriggerFilterGroup.PlaceLabledControl("Chest", this, &TriggerChest);

	TriggerStomach.SetFileId("trig_stomach");
	TriggerFilterGroup.PlaceLabledControl("Stomach", this, &TriggerStomach);

	TriggerArms.SetFileId("trig_arms");
	TriggerFilterGroup.PlaceLabledControl("Arms", this, &TriggerArms);

	TriggerLegs.SetFileId("trig_legs");
	TriggerFilterGroup.PlaceLabledControl("Legs", this, &TriggerLegs);

	TriggerTeammates.SetFileId("trig_teammates");
	TriggerFilterGroup.PlaceLabledControl("Friendly Fire", this, &TriggerTeammates);
#pragma endregion Triggerbot stuff

#pragma region Main Weapon
	WeaponMainGroup.SetPosition(16, 274);
	WeaponMainGroup.SetText("Rifles/Other");
	WeaponMainGroup.SetSize(240, 210);
	RegisterControl(&WeaponMainGroup);

	WeaponMainSpeed.SetFileId("main_speed");
	WeaponMainSpeed.SetBoundaries(0.1f, 2.f); 
	WeaponMainSpeed.SetValue(1.0f);
	WeaponMainGroup.PlaceLabledControl("Max Speed", this, &WeaponMainSpeed);

	WeaponMainFoV.SetFileId("main_fov");
	WeaponMainFoV.SetBoundaries(0.f, 30.f);
	WeaponMainFoV.SetValue(5.f);
	WeaponMainGroup.PlaceLabledControl("FoV", this, &WeaponMainFoV);

	WeaponMainRecoil.SetFileId("main_recoil");
	WeaponMainGroup.PlaceLabledControl("Recoil", this, &WeaponMainRecoil);

	WeaponMainPSilent.SetFileId("main_psilent");
	WeaponMainGroup.PlaceLabledControl("Silent", this, &WeaponMainPSilent);

	WeaponMainInacc.SetFileId("main_inacc");
	WeaponMainInacc.SetBoundaries(0.f, 15.f);
	WeaponMainGroup.PlaceLabledControl("Inaccuracy", this, &WeaponMainInacc);

	WeaponMainHitbox.SetFileId("main_hitbox");
	WeaponMainHitbox.AddItem("Head");
	WeaponMainHitbox.AddItem("Neck");
	WeaponMainHitbox.AddItem("Chest");
	WeaponMainHitbox.AddItem("Stomach");
	WeaponMainGroup.PlaceLabledControl("Primary Hitbox", this, &WeaponMainHitbox);

	WeaponMainSecHitbox.SetFileId("sec_hitbox");
	WeaponMainSecHitbox.AddItem("None");
	WeaponMainSecHitbox.AddItem("Head");
	WeaponMainSecHitbox.AddItem("Neck");
	WeaponMainSecHitbox.AddItem("Chest");
	WeaponMainSecHitbox.AddItem("Stomach");
	WeaponMainGroup.PlaceLabledControl("Secondary Hitbox", this, &WeaponMainSecHitbox);

#pragma endregion

#pragma region Pistols
	WeaponPistGroup.SetPosition(272, 274);
	WeaponPistGroup.SetText("Pistols");
	WeaponPistGroup.SetSize(240, 210);
	RegisterControl(&WeaponPistGroup);

	WeaponPistSpeed.SetFileId("pist_speed");
	WeaponPistSpeed.SetBoundaries(0.1f, 2.f);
	WeaponPistSpeed.SetValue(1.0f);
	WeaponPistGroup.PlaceLabledControl("Max Speed", this, &WeaponPistSpeed);

	WeaponPistFoV.SetFileId("pist_fov");
	WeaponPistFoV.SetBoundaries(0.1f, 5.f);
	WeaponPistFoV.SetValue(0.78f);
	WeaponPistGroup.PlaceLabledControl("FoV", this, &WeaponPistFoV);

	WeaponPistRecoil.SetFileId("pist_recoil");
	WeaponPistGroup.PlaceLabledControl("Recoil", this, &WeaponPistRecoil);

	WeaponPistPSilent.SetFileId("pist_psilent");
	WeaponPistGroup.PlaceLabledControl("Silent", this, &WeaponPistPSilent);

	WeaponPistInacc.SetFileId("pist_inacc");
	WeaponPistInacc.SetBoundaries(0.f, 15.f);
	WeaponPistInacc.SetValue(0.f);
	WeaponPistGroup.PlaceLabledControl("Inaccuracy", this, &WeaponPistInacc);

	WeaponPistHitbox.SetFileId("pist_hitbox");
	WeaponPistHitbox.AddItem("Head");
	WeaponPistHitbox.AddItem("Neck");
	WeaponPistHitbox.AddItem("Chest");
	WeaponPistHitbox.AddItem("Stomach");
	WeaponPistGroup.PlaceLabledControl("Primary Hitbox", this, &WeaponPistHitbox);

	WeaponPistSecHitbox.SetFileId("pist_sec_hitbox");
	WeaponPistSecHitbox.AddItem("None");
	WeaponPistSecHitbox.AddItem("Head");
	WeaponPistSecHitbox.AddItem("Neck");
	WeaponPistSecHitbox.AddItem("Chest");
	WeaponPistSecHitbox.AddItem("Stomach");
	WeaponPistGroup.PlaceLabledControl("Seconday Hitbox", this, &WeaponPistSecHitbox);
#pragma endregion

#pragma region Snipers
	WeaponSnipGroup.SetPosition(528, 274);
	WeaponSnipGroup.SetText("Snipers");
	WeaponSnipGroup.SetSize(240, 210);
	RegisterControl(&WeaponSnipGroup);

	

	WeaponSnipSpeed.SetFileId("wconf_speed_ak");
	WeaponSnipSpeed.SetBoundaries(0.1f, 2.f);
	WeaponSnipSpeed.SetValue(1.0f);
	WeaponSnipGroup.PlaceLabledControl("Max Speed", this, &WeaponSnipSpeed);

	WeaponSnipFoV.SetFileId("wconf_fov_ak");
	WeaponSnipFoV.SetBoundaries(0.1f, 30.f);
	WeaponSnipFoV.SetValue(5.f);
	WeaponSnipGroup.PlaceLabledControl("FoV", this, &WeaponSnipFoV);

	WeaponSnipRecoil.SetFileId("wconf_recoil_ak");
	WeaponSnipGroup.PlaceLabledControl("Recoil", this, &WeaponSnipRecoil);

	WeaponSnipPSilent.SetFileId("wconf_psilent_ak");
	WeaponSnipGroup.PlaceLabledControl("Silent", this, &WeaponSnipPSilent);

	WeaponSnipInacc.SetFileId("wconf_inacc_ak");
	WeaponSnipInacc.SetBoundaries(0.f, 15.f);
	WeaponSnipGroup.PlaceLabledControl("Inaccuracy", this, &WeaponSnipInacc);

	WeaponSnipHitbox.SetFileId("wconf_hitbox_ak");
	WeaponSnipHitbox.AddItem("Head");
	WeaponSnipHitbox.AddItem("Neck");
	WeaponSnipHitbox.AddItem("Chest");
	WeaponSnipHitbox.AddItem("Stomach");
	WeaponSnipGroup.PlaceLabledControl("Primary Hitbox", this, &WeaponSnipHitbox);

	WeaponSnipSecHitbox.SetFileId("wconf_hitbox_sec_ak");
	WeaponSnipSecHitbox.AddItem("None");
	WeaponSnipSecHitbox.AddItem("Head");
	WeaponSnipSecHitbox.AddItem("Neck");
	WeaponSnipSecHitbox.AddItem("Chest");
	WeaponSnipSecHitbox.AddItem("Stomach");
	WeaponSnipGroup.PlaceLabledControl("Secondary Hitbox", this, &WeaponSnipSecHitbox);
#pragma endregion

#pragma More
	


#pragma endregion
}

void CVisualTab::Setup()
{
	SetTitle("Visuals");

	ActiveLabel.SetPosition(16, 16);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(66, 16);
	RegisterControl(&Active);

#pragma region Options
	OptionsGroup.SetText("Options");
	OptionsGroup.SetPosition(16, 48);
	OptionsGroup.SetSize(193, 430);
	RegisterControl(&OptionsGroup);

	OptionsBox.SetFileId("opt_box");
	OptionsBox.AddItem("None");
	OptionsBox.AddItem("Corners");
	OptionsBox.AddItem("Full");
	OptionsGroup.PlaceLabledControl("Box", this, &OptionsBox);

	OptionsBox.SetFileId("opt_boxfill");
	OptionsGroup.PlaceLabledControl("Fill", this, &OptionsBoxFill);
	
	OptionsBox.SetFileId("opt_boxcolor");
	OptionsGroup.PlaceLabledControl("Colorize fill", this, &OptionsBoxFillColor);

	OptionIsDefusing.SetFileId("opt_hedufusinglel");
	OptionsGroup.PlaceLabledControl("Is Defusing", this, &OptionIsDefusing);

	OptionDefuser.SetFileId("opt_dontbealoserbuyadefuser");
	OptionsGroup.PlaceLabledControl("Has Defuser", this, &OptionDefuser);

	OptionIsScoped.SetFileId("opt_scoped");
	OptionsGroup.PlaceLabledControl("Is Scoped", this, &OptionIsScoped);

	OptionsName.SetFileId("opt_name");
	OptionsGroup.PlaceLabledControl("Name", this, &OptionsName);

	OptionsHealth.SetFileId("opt_hp");
	OptionsGroup.PlaceLabledControl("Health", this, &OptionsHealth);

	OptionsArmor.SetFileId("opt_arm");
	OptionsGroup.PlaceLabledControl("Armor", this, &OptionsArmor);

	OptionsDistance.SetFileId("opt_dist");
	OptionsGroup.PlaceLabledControl("Distance", this, &OptionsDistance);

	OptionsWeapon.SetFileId("opt_weapon");
	OptionsGroup.PlaceLabledControl("Weapon", this, &OptionsWeapon);

	OptionsInfo.SetFileId("opt_info");
	OptionsGroup.PlaceLabledControl("Info", this, &OptionsInfo);

	OptionsChams.SetFileId("opt_chams");
	OptionsChams.AddItem("Off");
	OptionsChams.AddItem("Normal");
	OptionsChams.AddItem("Flat");
	OptionsChams.AddItem("Visible Only - Normal");
	OptionsChams.AddItem("Visible Only - Flat");

	OptionsGroup.PlaceLabledControl("Chams", this, &OptionsChams);

	OptionsSkeleton.SetFileId("opt_bone");
	OptionsGroup.PlaceLabledControl("Skeleton", this, &OptionsSkeleton);

	OptionsVisibleOnly.SetFileId("opt_vonly");
	OptionsGroup.PlaceLabledControl("Visible Only", this, &OptionsVisibleOnly);

	OptionsAimSpot.SetFileId("opt_aimspot");
	OptionsGroup.PlaceLabledControl("Head Cross", this, &OptionsAimSpot);
	
	OptionsCompRank.SetFileId("opt_comprank");
	OptionsGroup.PlaceLabledControl("Player Ranks", this, &OptionsCompRank);
	

	OtherWireframe.SetFileId("opt_wireframe");
	OptionsGroup.PlaceLabledControl("Wireframe", this, &OtherWireframe);

	OtherGlow.SetFileId("opt_glow");
	OptionsGroup.PlaceLabledControl("Glow", this, &OtherGlow);
	
#pragma endregion Setting up the Options controls

#pragma region Filters
	FiltersGroup.SetText("Filters");
	FiltersGroup.SetPosition(225, 48);
	FiltersGroup.SetSize(193, 430);
	RegisterControl(&FiltersGroup);

	FiltersAll.SetFileId("ftr_all");
	FiltersGroup.PlaceLabledControl("All", this, &FiltersAll);

	FiltersPlayers.SetFileId("ftr_players");
	FiltersGroup.PlaceLabledControl("Players", this, &FiltersPlayers);

	FiltersEnemiesOnly.SetFileId("ftr_enemyonly");
	FiltersGroup.PlaceLabledControl("Enemies Only", this, &FiltersEnemiesOnly);

	FiltersWeapons.SetFileId("ftr_weaps");
	FiltersGroup.PlaceLabledControl("Weapons", this, &FiltersWeapons);

	FiltersChickens.SetFileId("ftr_chickens");
	FiltersGroup.PlaceLabledControl("Chickens", this, &FiltersChickens);

	FiltersC4.SetFileId("ftr_c4");
	FiltersGroup.PlaceLabledControl("C4", this, &FiltersC4);

	FiltersDead.SetFileId("ftr_spec");
	FiltersGroup.PlaceLabledControl("Only Dead", this, &FiltersDead);



#pragma endregion Setting up the Filters controls

#pragma region Other
	OtherGroup.SetText("Other");
	OtherGroup.SetPosition(434, 48);
	OtherGroup.SetSize(334, 430);
	RegisterControl(&OtherGroup);

	OtherCrosshair.SetFileId("otr_xhair");
	OtherGroup.PlaceLabledControl("Crosshair", this, &OtherCrosshair);

	OtherRecoilCrosshair.SetFileId("otr_recoilhair");
	OtherRecoilCrosshair.AddItem("Off");
	OtherRecoilCrosshair.AddItem("Recoil Position");
	OtherRecoilCrosshair.AddItem("Radius");
	OtherGroup.PlaceLabledControl("Recoil Crosshair", this, &OtherRecoilCrosshair);

	OtherRadar.SetFileId("otr_radar");
	OtherGroup.PlaceLabledControl("Radar", this, &OtherRadar);

	OtherNoVisualRecoil.SetFileId("otr_visrecoil");
	OtherGroup.PlaceLabledControl("No Visual Recoil", this, &OtherNoVisualRecoil);

	OtherNoFlash.SetFileId("otr_noflash");
	//OtherNoFlas.SetBoundaries(0.f, 90.f);
	//OtherViewmodelFOV.SetValue(0.f);
	OtherGroup.PlaceLabledControl("No Flash Enable", this, &OtherNoFlash);

	OtherNoFlashVal.SetFileId("otr_noflashval");
	OtherNoFlashVal.SetBoundaries(0,255);
	OtherViewmodelFOV.SetValue(200);
	OtherGroup.PlaceLabledControl("Max Flash", this, &OtherNoFlashVal);

/*	OtherNoHands.SetFileId("otr_hands");
	OtherNoHands.AddItem("Off");
	OtherNoHands.AddItem("None");
	OtherNoHands.AddItem("Transparent");
	OtherNoHands.AddItem("Chams");
	OtherNoHands.AddItem("Rainbow");
	OtherGroup.PlaceLabledControl("Hands", this, &OtherNoHands);*/

	OtherViewmodelFOV.SetFileId("otr_viewfov");
	OtherViewmodelFOV.SetBoundaries(0.f, 90.f);
	OtherViewmodelFOV.SetValue(0.f);
	OtherGroup.PlaceLabledControl("Viewmodel FOV Changer", this, &OtherViewmodelFOV);

	OtherFOV.SetFileId("otr_fov");
	OtherFOV.SetBoundaries(0.f, 180.f);
	OtherFOV.SetValue(90.f);
	OtherGroup.PlaceLabledControl("Field of View Changer", this, &OtherFOV);

	//OtherNoSky.SetFileId("otr_nosky");
	//OtherGroup.PlaceLabledControl("Darksky", this, &OtherNoSky);

	OtherNoScope.SetFileId("otr_noscope");
	OtherGroup.PlaceLabledControl("NoSocpe", this, &OtherNoScope);

	OtherNoSmoke.SetFileId("otr_nosmoke");
	OtherGroup.PlaceLabledControl("NoSmoke", this, &OtherNoSmoke);

	//OtherNoSmoke.SetFileId("otr_asus");
	//OtherGroup.PlaceLabledControl("AsusWalls", this, &OtherAsus);

	NightMode.SetFileId("otr_night");
	OtherGroup.PlaceLabledControl("NightMode", this, &NightMode);

	//ResetXD.SetText("Reset Stuff");
	//ResetXD.SetCallback(HooksXD::XD3);
	//OtherGroup.PlaceLabledControl("", this, &ResetXD);
	
#pragma endregion Setting up the Other controls
}

void CMiscTab::Setup()
{
	SetTitle("Misc");

#pragma region Knife
	/*KnifeGroup.SetPosition(16, 16);
	KnifeGroup.SetSize(360, 126);
	KnifeGroup.SetText("Knife Changer");
	RegisterControl(&KnifeGroup);

	KnifeEnable.SetFileId("knife_enable");
	KnifeGroup.PlaceLabledControl("Enable", this, &KnifeEnable);

	KnifeModel.SetFileId("knife_model");
	KnifeModel.AddItem("Karambit");
	KnifeModel.AddItem("Bayonet");
	KnifeModel.AddItem("M9 Bayonet");
	KnifeModel.AddItem("Flip Knife");
	KnifeModel.AddItem("Gut Knife");
	KnifeModel.AddItem("Huntsman Knife");
	KnifeModel.AddItem("Falchion Knife");
    KnifeModel.AddItem("Bowie Knife");
	KnifeModel.AddItem("Butterfly Knife");
	KnifeModel.AddItem("Shadow Daggers");
	KnifeGroup.PlaceLabledControl("Knife", this, &KnifeModel);

	KnifeSkin.SetFileId("knife_skin");
	KnifeSkin.AddItem("Doppler Sapphire");
	KnifeSkin.AddItem("Doppler Ruby");
	KnifeSkin.AddItem("Tiger Tooth");
	KnifeSkin.AddItem("Lore");
	KnifeSkin.AddItem("Forest DDPAT");
	KnifeSkin.AddItem("Crimson Web");
	KnifeSkin.AddItem("Slaughter");
	KnifeSkin.AddItem("Vanilla");
	KnifeSkin.AddItem("Fade");
	KnifeSkin.AddItem("Night");
	KnifeSkin.AddItem("Blue Steel");
	KnifeSkin.AddItem("Stained");
	KnifeSkin.AddItem("Case Hardended");
	KnifeSkin.AddItem("Safari Mesh");
	KnifeSkin.AddItem("Boreal Forest");
	KnifeSkin.AddItem("Ultaviolet");
	KnifeSkin.AddItem("Rust Coat");
	KnifeSkin.AddItem("Romania's Flag <3");
	

	KnifeGroup.PlaceLabledControl("Skin", this, &KnifeSkin);

	KnifeApply.SetText("Apply Knife");
	KnifeApply.SetCallback(KnifeApplyCallbk);
	KnifeGroup.PlaceLabledControl("", this, &KnifeApply);
*/
#pragma endregion

#pragma region Other
	OtherGroup.SetPosition(408, 16);
	OtherGroup.SetSize(360, 260);
	OtherGroup.SetText("Other");
	RegisterControl(&OtherGroup);

	OtherAutoJump.SetFileId("otr_autojump");
	OtherGroup.PlaceLabledControl("Bhop", this, &OtherAutoJump);

//	OtherAutoJump.SetFileId("otr_hautojump");
//	OtherGroup.PlaceLabledControl("Humanized Bhop", this, &OtherHAutoJump); 

	OtherEdgeJump.SetFileId("otr_edgejump");
	OtherGroup.PlaceLabledControl("Edge Jump", this, &OtherEdgeJump);

	OtherAutoStrafe.SetFileId("otr_strafe");
	OtherAutoStrafe.AddItem("Off");
	OtherAutoStrafe.AddItem("Legit");
	OtherAutoStrafe.AddItem("Rage");
	OtherGroup.PlaceLabledControl("Auto Strafer", this, &OtherAutoStrafe);

	OtherAutoCounterStafe.SetFileId("otr_autocs");
	OtherGroup.PlaceLabledControl("Auto Counter-Stafer Enable", this, &OtherAutoCounterStafe);

	OtherAutoCounterStafeKey.SetFileId("otr_autocs_key");
	OtherGroup.PlaceLabledControl("Auto Counter-Stafer Key", this, &OtherAutoCounterStafeKey);

	OtherSafeMode.SetFileId("otr_safemode");
	OtherSafeMode.SetState(true);
	OtherGroup.PlaceLabledControl("Safe Mode", this, &OtherSafeMode);






	OtherThirdperson.SetFileId("aa_thirdpsr");
	OtherGroup.PlaceLabledControl("Thirdperson", this, &OtherThirdperson);


	OtherThirdpersonFake.SetFileId("aa_thirdpsrfake");
	OtherGroup.PlaceLabledControl("TP ShowFake?", this, &OtherThirdpersonFake);



	//DisableAll.SetFileId("otr_disableall");
	//OtherGroup.PlaceLabledControl("Disable All", this, &DisableAll);

#pragma endregion other random options

#pragma region FakeLag
	FakeLagGroup.SetPosition(16, 16);
	FakeLagGroup.SetSize(360, 141);
	FakeLagGroup.SetText("Fake Lag");
	RegisterControl(&FakeLagGroup);

	FakeLagEnable.SetFileId("fakelag_enable");
	FakeLagGroup.PlaceLabledControl("Fake Lag", this, &FakeLagEnable);

	FakeLagChoke.SetFileId("fakelag_choke");
	FakeLagChoke.SetBoundaries(0, 16);
	FakeLagChoke.SetValue(0);
	FakeLagGroup.PlaceLabledControl("Choke Factor", this, &FakeLagChoke);

	FakeLagSend.SetFileId("fakelag_send");
	FakeLagSend.SetBoundaries(0, 16);
	FakeLagSend.SetValue(0);
	FakeLagGroup.PlaceLabledControl("Send Factor", this, &FakeLagSend);

	ChokeRandomize.SetFileId("choke_random");
	FakeLagGroup.PlaceLabledControl("Randomize Choke", this, &ChokeRandomize);

	SendRandomize.SetFileId("send_random");
	FakeLagGroup.PlaceLabledControl("Randomize Send", this, &SendRandomize);
#pragma endregion fakelag shit




/*#pragma region OverideFov
	FOVGroup.SetPosition(16, 365);
	FOVGroup.SetSize(360, 75);
	FOVGroup.SetText("FOV Changer");
	RegisterControl(&FOVGroup);

	FOVEnable.SetFileId("fov_enable");
	FOVGroup.PlaceLabledControl("Enable", this, &FOVEnable);

	FOVSlider.SetFileId("fov_slider");
	FOVSlider.SetBoundaries(0, 200);
	FOVSlider.SetValue(0);
	FOVGroup.PlaceLabledControl("FOV Amount", this, &FOVSlider);

#pragma endregion*/
}

/*void CPlayersTab::Setup()
{
	SetTitle("PlayerList");

#pragma region PList

	pListGroup.SetPosition(16, 16);
	pListGroup.SetSize(680, 200);
	pListGroup.SetText("Player List");
	pListGroup.SetColumns(2);
	RegisterControl(&pListGroup);

	pListPlayers.SetPosition(26, 46);
	pListPlayers.SetSize(640, 50);
	pListPlayers.SetHeightInItems(20);
	RegisterControl(&pListPlayers);

#pragma endregion

#pragma region Options
	
	OptionsGroup.SetPosition(16, 257);
	OptionsGroup.SetSize(450, 120);
	OptionsGroup.SetText("Player Options");
	RegisterControl(&OptionsGroup);

	OptionsFriendly.SetFileId("pl_friendly");
	OptionsGroup.PlaceLabledControl("Friendly", this, &OptionsFriendly);

	OptionsAimPrio.SetFileId("pl_priority");
	OptionsGroup.PlaceLabledControl("Priority", this, &OptionsAimPrio);

	OptionsCalloutSpam.SetFileId("pl_callout");
	OptionsGroup.PlaceLabledControl("Callout Spam", this, &OptionsCalloutSpam);

#pragma endregion
}

DWORD GetPlayerListIndex(int EntId)
{
	player_info_t pinfo;
	Interfaces::Engine->GetPlayerInfo(EntId, &pinfo);

	// Bot
	if (pinfo.guid[0] == 'B' && pinfo.guid[1] == 'O')
	{
		char buf[64]; sprintf_s(buf, "BOT_420%sAY", pinfo.name);
		return CRC32(buf, 64);
	}
	else
	{
		return CRC32(pinfo.guid, 32);
	}
}

bool IsFriendly(int EntId)
{
	DWORD plistId = GetPlayerListIndex(EntId);
	if (PlayerList.find(plistId) != PlayerList.end())
	{
		return PlayerList[plistId].Friendly;
	}

	return false;
}

bool IsAimPrio(int EntId)
{
	DWORD plistId = GetPlayerListIndex(EntId);
	if (PlayerList.find(plistId) != PlayerList.end())
	{
		return PlayerList[plistId].AimPrio;
	}

	return false;
}

bool IsCalloutTarget(int EntId)
{
	DWORD plistId = GetPlayerListIndex(EntId);
	if (PlayerList.find(plistId) != PlayerList.end())
	{
		return PlayerList[plistId].Callout;
	}

	return false;
}

void UpdatePlayerList()
{
	IClientEntity* pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame() && pLocal && pLocal->IsAlive())
	{
		Menu::Window.Playerlist.pListPlayers.ClearItems();

		// Loop through all active entitys
		for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
		{
			// Get the entity

			player_info_t pinfo;
			if (i != Interfaces::Engine->GetLocalPlayer() && Interfaces::Engine->GetPlayerInfo(i, &pinfo))
			{
				IClientEntity* pEntity = Interfaces::EntList->GetClientEntity(i);
				int HP = 100; char* Location = "Unknown";
				char *Friendly = " ", *AimPrio = " ";

				DWORD plistId = GetPlayerListIndex(Menu::Window.Playerlist.pListPlayers.GetValue());
				if (PlayerList.find(plistId) != PlayerList.end())
				{
					Friendly = PlayerList[plistId].Friendly ? "Friendly" : "";
					AimPrio = PlayerList[plistId].AimPrio ? "AimPrio" : "";
				}

				if (pEntity && !pEntity->IsDormant())
				{
					HP = pEntity->GetHealth();
					Location = pEntity->GetLastPlaceName();
				}

				char nameBuffer[512];
				sprintf_s(nameBuffer, "%-24s %-10s %-10s [%d HP] [Last Seen At %s]", pinfo.name, IsFriendly(i) ? "Friend" : " ", IsAimPrio(i) ? "AimPrio" : " ", HP, Location);
				Menu::Window.Playerlist.pListPlayers.AddItem(nameBuffer, i);

			}

		}

		DWORD meme = GetPlayerListIndex(Menu::Window.Playerlist.pListPlayers.GetValue());

		// Have we switched to a different player?
		static int PrevSelectedPlayer = 0;
		if (PrevSelectedPlayer != Menu::Window.Playerlist.pListPlayers.GetValue())
		{
			if (PlayerList.find(meme) != PlayerList.end())
			{
				Menu::Window.Playerlist.OptionsFriendly.SetState(PlayerList[meme].Friendly);
				Menu::Window.Playerlist.OptionsAimPrio.SetState(PlayerList[meme].AimPrio);
				Menu::Window.Playerlist.OptionsCalloutSpam.SetState(PlayerList[meme].Callout);

			}
			else
			{
				Menu::Window.Playerlist.OptionsFriendly.SetState(false);
				Menu::Window.Playerlist.OptionsAimPrio.SetState(false);
				Menu::Window.Playerlist.OptionsCalloutSpam.SetState(false);

			}
		}
		PrevSelectedPlayer = Menu::Window.Playerlist.pListPlayers.GetValue();

		PlayerList[meme].Friendly = Menu::Window.Playerlist.OptionsFriendly.GetState();
		PlayerList[meme].AimPrio = Menu::Window.Playerlist.OptionsAimPrio.GetState();
		PlayerList[meme].Callout = Menu::Window.Playerlist.OptionsCalloutSpam.GetState();
	}
}*/

void CColorTab::Setup()
{
	SetTitle("Colors");
#pragma region Colors
	CTNVisGroup.SetPosition(16, 16);
	CTNVisGroup.SetSize(360, 100);
	CTNVisGroup.SetText("CT Not Visible");
	RegisterControl(&CTNVisGroup);

	// CT NOT VISIBLE
	CTNVisColorR.SetFileId("ct_not_vis_r");
	CTNVisColorR.SetBoundaries(1, 255);
	CTNVisColorR.SetValue(15);
	CTNVisGroup.PlaceLabledControl("Red", this, &CTNVisColorR);

	CTNVisColorG.SetFileId("ct_not_vis_g");
	CTNVisColorG.SetBoundaries(1, 255);
	CTNVisColorG.SetValue(1);
	CTNVisGroup.PlaceLabledControl("Green", this, &CTNVisColorG);

	CTNVisColorB.SetFileId("ct_not_vis_b");
	CTNVisColorB.SetBoundaries(1, 255);
	CTNVisColorB.SetValue(220);
	CTNVisGroup.PlaceLabledControl("Blue", this, &CTNVisColorB);



	//CT VISIBLE
	CTVisGroup.SetPosition(408, 16);
	CTVisGroup.SetSize(360, 100);
	CTVisGroup.SetText("CT Visible");
	RegisterControl(&CTVisGroup);

	CTVisColorR.SetFileId("ct_vis_r");
	CTVisColorR.SetBoundaries(1, 255);
	CTVisColorR.SetValue(187);
	CTVisGroup.PlaceLabledControl(" Red", this, &CTVisColorR);

	CTVisColorG.SetFileId("ct_vis_g");
	CTVisColorG.SetBoundaries(1, 255);
	CTVisColorG.SetValue(1);
	CTVisGroup.PlaceLabledControl("Green", this, &CTVisColorG);

	CTVisColorB.SetFileId("ct_vis_b");
	CTVisColorB.SetBoundaries(1, 255);
	CTVisColorB.SetValue(255);
	CTVisGroup.PlaceLabledControl("Blue", this, &CTVisColorB);

	//T Not Visible
	TNVisGroup.SetPosition(16, 137);
	TNVisGroup.SetSize(360, 100);
	TNVisGroup.SetText("T Not Visible");
	RegisterControl(&TNVisGroup);

	TNVisColorR.SetFileId("t_not_vis_r");
	TNVisColorR.SetBoundaries(1, 255);
	TNVisColorR.SetValue(235);
	TNVisGroup.PlaceLabledControl("Red", this, &TNVisColorR);

	TNVisColorG.SetFileId("t_not_vis_g");
	TNVisColorG.SetBoundaries(1, 255);
	TNVisColorG.SetValue(50);
	TNVisGroup.PlaceLabledControl("Red", this, &TNVisColorG);

	TNVisColorB.SetFileId("t_not_vis_b");
	TNVisColorB.SetBoundaries(1, 255);
	TNVisColorB.SetValue(1);
	TNVisGroup.PlaceLabledControl("Blue", this, &TNVisColorB);

	// T Vis Color

	TVisGroup.SetPosition(408, 137);
	TVisGroup.SetSize(360, 100);
	TVisGroup.SetText("T Visible");
	RegisterControl(&TVisGroup);

	TVisColorR.SetFileId("t_vis_r");
	TVisColorR.SetBoundaries(1, 255);
	TVisColorR.SetValue(255);
	TVisGroup.PlaceLabledControl("Red", this, &TVisColorR);

	TVisColorG.SetFileId("t_vis_g");
	TVisColorG.SetBoundaries(1, 255);
	TVisColorG.SetValue(200);
	TVisGroup.PlaceLabledControl("Green", this, &TVisColorG);

	TVisColorB.SetFileId("t_vis_b");
	TVisColorB.SetBoundaries(1, 255);
	TVisColorB.SetValue(1);
	TVisGroup.PlaceLabledControl("Blue", this, &TVisColorB);


#pragma endregion
	
#pragma MenuGroup
	MenuGroup.SetPosition(16, 258);
	MenuGroup.SetSize(360, 100);
	MenuGroup.SetText("Bar Color 1");
	RegisterControl(&MenuGroup);

	//Menu Gradient Color 1
	MenuBar1R.SetFileId("bar_grad_1R");
	MenuBar1R.SetBoundaries(0, 255);
	MenuBar1R.SetValue(255);
	MenuGroup.PlaceLabledControl("Red", this, &MenuBar1R);

	MenuBar1G.SetFileId("bar_grad_1G");
	MenuBar1G.SetBoundaries(0, 255);
	MenuBar1G.SetValue(144);
	MenuGroup.PlaceLabledControl("Green", this, &MenuBar1G);

	MenuBar1B.SetFileId("bar_grad_1B");
	MenuBar1B.SetBoundaries(0, 255);
	MenuBar1B.SetValue(0);
	MenuGroup.PlaceLabledControl("Blue", this, &MenuBar1B);


	//Menu Gradient Color 2
	MenuBar2.SetPosition(408, 258);
	MenuBar2.SetSize(360, 100);
	MenuBar2.SetText("Bar Color 2");
	RegisterControl(&MenuBar2);

	MenuBar2R.SetFileId("bar_grad_2R");
	MenuBar2R.SetBoundaries(0, 255);
	MenuBar2R.SetValue(255);
	MenuBar2.PlaceLabledControl("Red", this, &MenuBar2R);

	MenuBar2G.SetFileId("bar_grad_2G");
	MenuBar2G.SetBoundaries(0, 255);
	MenuBar2G.SetValue(93);
	MenuBar2.PlaceLabledControl("Green", this, &MenuBar2G);

	MenuBar2B.SetFileId("bar_grad_2B");
	MenuBar2B.SetBoundaries(0, 255);
	MenuBar2B.SetValue(0);
	MenuBar2.PlaceLabledControl("Blue", this, &MenuBar2B);


	//MenuOpacity.SetFileId("men_oapacity");
	//MenuOpacity.SetBoundaries(0, 255);
	//MenuOpacity.SetValue(0);
	//MenuGroup.PlaceLabledControl("Menu Opacity", this, &MenuOpacity);

	//Inner
	MenuInside.SetPosition(16, 379);
	MenuInside.SetSize(360, 100);
	MenuInside.SetText("Menu Inner Color");
	RegisterControl(&MenuInside);

	MenuInnerR.SetFileId("in_R");
	MenuInnerR.SetBoundaries(0, 255);
	MenuInnerR.SetValue(255);
	MenuInside.PlaceLabledControl("Red", this, &MenuInnerR);

	MenuInnerG.SetFileId("in_G");
	MenuInnerG.SetBoundaries(0, 255);
	MenuInnerG.SetValue(93);
	MenuInside.PlaceLabledControl("Green", this, &MenuInnerG);

	MenuInnerB.SetFileId("in_B");
	MenuInnerB.SetBoundaries(0, 255);
	MenuInnerB.SetValue(0);
	MenuInside.PlaceLabledControl("Stuff", this, &MenuInnerB);

	//Menu Background

	MenuBackround.SetPosition(408, 379);
	MenuBackround.SetSize(360, 135);
	MenuBackround.SetText("More");
	RegisterControl(&MenuBackround);

	CharmsA.SetFileId("charms_a");
	CharmsA.SetBoundaries(0, 255);
	CharmsA.SetValue(255);
	MenuBackround.PlaceLabledControl("Charms Alpha", this, &CharmsA);


#pragma endregion

}

void CSettingsTab::Setup()
{

	SetTitle("Settings");
#pragma ButtonGroup
	ButtonGroup.SetPosition(16, 16);
	ButtonGroup.SetSize(360, 460);
	ButtonGroup.SetText("Buttons");
	RegisterControl(&ButtonGroup);

	SaveButton.SetText("Save Configuration");
	SaveButton.SetCallback(SaveCallbk);
	ButtonGroup.PlaceLabledControl("Save", this, &SaveButton);

	LoadButton.SetText("Load Configuration");
	LoadButton.SetCallback(LoadCallbk);
	ButtonGroup.PlaceLabledControl("Load", this, &LoadButton);

	//Options


	SetNr.AddItem("Legit");
	SetNr.AddItem("Semi Rage");
	SetNr.AddItem("Rage");
	SetNr.AddItem("FaceIT 1");
	SetNr.AddItem("FaceIT 2");
	SetNr.AddItem("NoSpread 1");
	SetNr.AddItem("Nospread 2");
	ButtonGroup.PlaceLabledControl("Config: ", this, &SetNr);

	Unload.SetText("Force Crash(time out)");
	Unload.SetCallback(Unloadbk);
	ButtonGroup.PlaceLabledControl("", this, &Unload);
};


	
#pragma endregion other random options


void Menu::SetupMenu()
{
	Window.Setup();

	GUI.RegisterWindow(&Window);
	GUI.BindWindow(VK_INSERT, &Window);
}

void Menu::DoUIFrame()
{
	static bool sumfuk = false;
	if (!sumfuk)
	{
		
	}
	// General Processing

	// If the "all filter is selected tick all the others
	if (Window.VisualsTab.FiltersAll.GetState())
	{
		Window.VisualsTab.FiltersC4.SetState(true);
		Window.VisualsTab.FiltersChickens.SetState(true);
		Window.VisualsTab.FiltersPlayers.SetState(true);
		Window.VisualsTab.FiltersWeapons.SetState(true);
	}


	if (Window.MiscTab.OtherHAutoJump.GetState())
	{
		Window.MiscTab.OtherAutoJump.SetState(false);
	}

	if (Window.MiscTab.OtherAutoJump.GetState())
	{
		Window.MiscTab.OtherHAutoJump.SetState(false);
	}
	

	GUI.Update();
	GUI.Draw();

	
}


