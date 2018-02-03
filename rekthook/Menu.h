

#pragma once

#include "GUI.h"
#include "Controls.h"

class CRageBotTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Aimbot Settings
	CGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CSlider	  AimbotFov;
	CCheckBox AimbotSilentAim;
	CCheckBox AimbotPerfectSilentAim;
	CCheckBox AimbotAutoPistol;
	CCheckBox AimbotAutoRevolver;
	CCheckBox AimbotAimStep;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CKeyBind  AimbotStopKey;
	CCheckBox LowerbodyFix;
	CComboBox AimbotResolver;
	CCheckBox AdvancedResolver;
	CCheckBox PreferBodyAim;
	CCheckBox LBY;
	CComboBox FakeYaw;
	CSlider BaimIfUnderXHealth;

	// Target Selection Settings
	CGroupBox TargetGroup;
	CComboBox TargetSelection;
	CCheckBox TargetFriendlyFire;
	CComboBox TargetHitbox;
	CComboBox TargetHitscan;
	CCheckBox TargetMultipoint;
	CSlider   TargetPointscale;
	CSlider AimbotAutoPistolD;
	// Accuracy Settings
	CGroupBox AccuracyGroup;
	CCheckBox AccuracyRecoil;
	CCheckBox AccuracyAutoWall;
	CSlider	  AccuracyMinimumDamage;
	CCheckBox AccuracyAutoStop;
	CCheckBox AccuracyAutoCrouch;
	CCheckBox AccuracyAutoScope;
	CSlider   AccuracyHitchance;
	CComboBox AccuracyResolver;
	CCheckBox AccuracyPositionAdjustment;
	CSlider   AccuracySmart;

	// Anti-Aim Settings
	CGroupBox AntiAimGroup;
	CCheckBox AntiAimEnable;
	CComboBox AntiAimPitch;
	CComboBox AntiAimYaw;
	CComboBox AntiAimYawFake;


	CSlider   AccuracyTickCount;
	CSlider   AccuracyNumber;
	CSlider   AccuracyVelocit;

	CKeyBind  AimbotKeyFakeWalk;
	CCheckBox AimbotExtraResolver;
	CCheckBox AimbotChangeSideAA;

	CKeyBind  AimbotBaimOnKey;
	CKeyBind  AimbotTargetSide;

	CCheckBox AntiAimLBY;


	CCheckBox AntiAimEdge;
	CSlider	  AntiAimOffset;
	CSlider AntiAimSpinbot;

	CCheckBox AntiAimKnife;
	CSlider   AntiAimSpeed;
	CCheckBox AntiAimTarget;

};

class CLegitBotTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Aimbot Settings
	CGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CCheckBox AimbotFriendlyFire;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CCheckBox AimbotAutoPistol;
	CSlider   AimbotInaccuracy;
	CKeyBind  AimbotDisableVis;

	// Main
	CGroupBox TriggerGroup;
	CCheckBox TriggerEnable;
	CCheckBox TriggerKeyPress;
	CKeyBind  TriggerKeyBind;
	CSlider  TriggerDelay;

	// Main
	CGroupBox WeaponMainGroup;
	CSlider   WeaponMainSpeed;
	CSlider   WeaponMainFoV;
	CCheckBox WeaponMainRecoil;
	CCheckBox WeaponMainPSilent;
	CSlider   WeaponMainInacc;
	CComboBox WeaponMainHitbox;
	CComboBox WeaponMainSecHitbox;

	// Pistol
	CGroupBox WeaponPistGroup;
	CSlider   WeaponPistSpeed;
	CSlider   WeaponPistFoV;
	CCheckBox WeaponPistRecoil;
	CCheckBox WeaponPistPSilent;
	CSlider   WeaponPistInacc;
	CComboBox WeaponPistHitbox;
	CComboBox WeaponPistSecHitbox;
	// Sniper
	CCheckBox WeaponSnipEnable;
	CGroupBox WeaponSnipGroup;
	CSlider   WeaponSnipSpeed;
	CSlider   WeaponSnipFoV;
	CCheckBox WeaponSnipRecoil;
	CCheckBox WeaponSnipPSilent;
	CSlider   WeaponSnipInacc;
	CComboBox WeaponSnipHitbox;
	CComboBox WeaponSnipSecHitbox;

	CGroupBox TriggerFilterGroup;

	CCheckBox TriggerHead;
	CCheckBox TriggerChest;
	CCheckBox TriggerStomach;
	CCheckBox TriggerArms;
	CCheckBox TriggerLegs;
	CCheckBox TriggerTeammates;
	CCheckBox TriggerRecoil;
	//More
	CGroupBox AimMoreGroup;
	CCheckBox FoVRadius;
	CCheckBox WeaponConfig;
	CComboBox WeaponConf;
};

class CVisualTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Options Settings
	CGroupBox OptionsGroup;
	CComboBox OptionsBox;
	CCheckBox OptionsBoxFill;
	CCheckBox OptionsBoxFillColor;
	CCheckBox OptionIsDefusing;
	CCheckBox OptionDefuser;
	CCheckBox OptionIsScoped;
	CCheckBox OptionsName;
	CCheckBox OptionsHealth;
	CCheckBox OptionsArmor;
	CCheckBox OptionsDistance;
	CCheckBox OptionsWeapon;
	CCheckBox OptionsInfo;
	CCheckBox OptionsHelmet;
	CCheckBox OptionsKit;
	CCheckBox OptionsDefuse;
	CCheckBox OtherWireframe;
	//CCheckBox OptionsGlow;
	CComboBox OptionsChams;
	CCheckBox OptionsSkeleton;
	CCheckBox OptionsVisibleOnly;
	CCheckBox OptionsAimSpot;
	CCheckBox OptionsCompRank;
	CCheckBox OtherAsus;
	// Skeleton ESP Colour
	CGroupBox ESPColorSkeleton;
	CComboBox ControlColor;
	CSlider   RSkele;
	CSlider   GSkele;
	CSlider   BSkele;
	CSlider   ASkele;

	// Filters Settings
	CGroupBox FiltersGroup;
	CCheckBox FiltersAll;
	CCheckBox FiltersPlayers;
	CCheckBox FiltersEnemiesOnly;
	CCheckBox FiltersWeapons;
	CCheckBox FiltersChickens;
	CCheckBox FiltersC4;
	CCheckBox FiltersDead;

	// Other Settings
	CGroupBox OtherGroup;
	CCheckBox OtherCrosshair;
	CComboBox OtherRecoilCrosshair;
	CCheckBox OtherHitmarker;
	CCheckBox OtherRadar;
	CCheckBox OtherNoVisualRecoil;
//	CCheckBox OtherNoSky; 
	CCheckBox OtherNoFlash; 
	CSlider   OtherNoFlashVal;
	CCheckBox OtherGlow;
	CCheckBox NightMode;
	CButton ResetXD;
	CCheckBox OtherNoSmoke;
	CCheckBox OtherAsusWalls;
	CComboBox OtherNoHands;
	CSlider OtherViewmodelFOV;
	CSlider OtherFOV;
	CCheckBox OtherNoScope;


};

class CMiscTab : public CTab
{
public:
	void Setup();

	// Knife Changer
	/*CGroupBox KnifeGroup;
	CCheckBox KnifeEnable;
	CComboBox KnifeModel;
	CComboBox KnifeSkin;
	CButton   KnifeApply;*/

	// Other Settings
	CGroupBox OtherGroup;
	CCheckBox OtherAutoJump;
	CCheckBox OtherHAutoJump;
	CCheckBox OtherEdgeJump;
	CComboBox OtherAutoStrafe;
	CCheckBox OtherSafeMode;
	CComboBox OtherChatSpam;
	CCheckBox OtherTeamChat;
	CSlider	  OtherChatDelay;
	CKeyBind  OtherLagSwitch;
	CCheckBox OtherSpectators;
	CCheckBox OtherThirdperson;
	CCheckBox OtherThirdpersonFake;
	CCheckBox OtherSkinChanger;
	CCheckBox OtherWatermark;
	CCheckBox OtherAutoCounterStafe;
	CKeyBind  OtherAutoCounterStafeKey;
	//CCheckBox OtherAutoAccept;
	CCheckBox OtherWalkbot;
//	CComboBox OtherClantag;
	CCheckBox DisableAll;
	CGroupBox MPGroup;
	CComboBox MAC10Skin;
	CComboBox P90Skin;
	CComboBox UMP45Skin;
	CComboBox BIZONSkin;
	CComboBox MP7Skin;
	CComboBox MP9Skin;
	
	CButton NApply;
	// Fake Lag Settings
	CGroupBox FakeLagGroup;
	CCheckBox FakeLagEnable;
	CSlider  FakeLagChoke;
	CSlider  FakeLagSend;
	CCheckBox ChokeRandomize;
	CCheckBox SendRandomize;
	//CCheckBox FakeLagWhileShooting;
};
class CColorTab : public CTab
{
public:
	void Setup();

	//Groups
	CSlider CharmsA;
	CGroupBox ColorsGroup;
	CGroupBox CTNVisGroup;
	CGroupBox CTVisGroup;
	CGroupBox TNVisGroup;
	CGroupBox TVisGroup;
	//Menu Groups
	CGroupBox MenuGroup;
	CGroupBox MenuBar2;
	CGroupBox MenuInside;
	CGroupBox MenuBackround;
	//CT Not Visible
	CSlider  CTNVisColorR;
	CSlider  CTNVisColorG;
	CSlider  CTNVisColorB;
	//CT Visible
	CSlider  CTVisColorR;
	CSlider  CTVisColorG;
	CSlider  CTVisColorB;
	//T Not Visible
	CSlider  TNVisColorR;
	CSlider  TNVisColorG;
	CSlider  TNVisColorB;
	//T Visible
	CSlider  TVisColorR;
	CSlider  TVisColorG;
	CSlider  TVisColorB;

	//Menu Colors

	
	CSlider  MenuBar1R;
	CSlider  MenuBar1G;
	CSlider  MenuBar1B;
	CSlider  MenuBar2R;
	CSlider  MenuBar2G;
	CSlider  MenuBar2B;
	//Inner
	CSlider  MenuInnerR;
	CSlider  MenuInnerG;
	CSlider  MenuInnerB;

	CSlider  MenuBGR;
	CSlider  MenuBGG;
	CSlider  MenuBGB;
	CSlider  MenuOpacity;
};


class CSettingsTab : public CTab
{
public:
	void Setup();
	CGroupBox ButtonGroup;
	CButton SaveButton;
	CButton LoadButton;
	//Options
	CComboBox SetNr;
	CButton Unload;
	

	
};
class rekthookwindow : public CWindow
{
public:
	void Setup();

	CRageBotTab RageBotTab;
	CLegitBotTab LegitBotTab;
	CVisualTab VisualsTab;
	CMiscTab MiscTab;
	CColorTab ColorTab;
	CSettingsTab SettingsTab;
	

	CButton SaveButton;
	CButton LoadButton;
	CButton UnloadButton;
};

namespace Menu
{
	void SetupMenu();
	void DoUIFrame();

	extern rekthookwindow Window;
};