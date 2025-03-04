#pragma once
#include "Component.h"

enum class PLAYER_STATE : uint8
{
	IDLE,
	WALK,

	DIE,
	END
};

enum class PLAYER_WEAPON : uint8
{
	PISTOL,
	SMG,
	SHOTGUN,
	SNIPER,
	NONE,
	END
};

enum class BULLET_STATE : uint8
{
	LIVE,
	SHOOT,
	DEAD,
	END
};

enum class MUZZLEFLASH_STATE : uint8
{
	LIVE,
	SHOOT,
	DEAD,
	END
};

class Player : public Component
{
public:
	Player();
	virtual ~Player();

public:
	virtual void Start() override;
	virtual void Update() override;
	void PlayerRotate();
	void ChangeWeapon(PLAYER_WEAPON weapon, bool swap);
	vector<shared_ptr<GameObject>> GetBullet() { return bullets; };
	vector<shared_ptr<GameObject>>	GetGun() { return gunObject; };
	vector<shared_ptr<GameObject>>	GetMuzzleFlash() { return muzzleFlashObject; };

public:
	void SetBulletPos(Vec3 pos) { cameraPosForBullet = pos; };
	void SetBulletLook(Vec3 Look) { cameraLookForBullet = Look; };

	int GetDamage() { return _damage; };
	int GetHP() { return _hp; };
	int GetCurrAmmo(PLAYER_WEAPON weapon);
	int GetMaxAmmo();
	PLAYER_WEAPON GetCurrWeapon() { return _currWeapon; };
	float GetCurrStamina() { return _stamina; };
	int GetMoney() { return _money; };
	float GetRecoil() { return _weaponRecoil; };
	bool GetWeaponChanged() { return _weaponChanged; };
	float GetPrice(bool gun, PLAYER_WEAPON weapon);
	bool GetWeaponInventory(PLAYER_WEAPON weapon) { return weapons[weapon]; };
	void SetHP(int hp) { _hp = hp; if (_hp > 100) _hp = 100; };
	void MakeMuzzleFlash();
	void MakeBullet();

	void AddMaxAmmo(PLAYER_WEAPON weapon);
	
	void Bleeding();
	shared_ptr<GameObject> GetBleeding() { return bleedingUI; };
	void SetRotateLock(bool lock) { _rotateLock = lock; };
	void SetShopOpened(bool open) { _shopOpened = open; };
	bool MoneyChange(int amount);
	void Reload();
	void BulletMuzzleFlashErase();

	void collisionFront(bool front) { _front = front; };
	void collisionBack(bool back) { _back = back; };
	void collisionRight(bool right) { _right = right; };
	void collisionLeft(bool left) { _left = left; };

	void Reset();

private:
	// Sound
	bool			_reloadsound = false;

	// Button
	bool			_frontButton = false;
	bool			_backButton = false;
	bool			_leftButton = false;
	bool			_rightButton = false;

	// Move
	bool			_front = false;
	bool			_back = false;
	bool			_right = false;
	bool			_left = false;
	bool			_moveHorizon = false;
	bool			_moveVertical = false;
	bool			_jump = false;
	int				_isMoving = 0;
	bool			_running = false;
	float			_stamina = 100;

	// Shop
	bool			_rotateLock = false;
	bool			_shopOpened = false;

	// Mouse
	POINT			_mousePos = {};
	POINT			_oldMousePos = {};
	float			_cxdelta = 0.f;

	// Status
	float			_speed = 2500.0f;
	int				_hp = 100;
	int				_Magazine = 0;
	bool			_reloading = false;
	float			_curRateOfFire = 0.f;
	bool			_isShot = false;
	int				_money = 900;
	float			_recoil = 0;
	shared_ptr<GameObject> bleedingUI;

	// Weapon
	PLAYER_WEAPON	_currWeapon = PLAYER_WEAPON::NONE;
	map<PLAYER_WEAPON, bool> weapons;
	int				_currMagazine = 0;
	int				_maxAmmo = 0;
	int				_damage = 25;
	int				_pellet = 0;
	int				_reloadPerAmmo = 0;
	float			_rateOfFire = 0.5f;
	float			_reloadMaxTime = 3.f;
	float			_reloadTime = 3.f;
	int				_price = 0;
	int				_accuracy = 5000;
	float			_weaponRecoil = 10;
	bool			_readyToShot = true;
	bool			_fullauto = false;
	bool			_isShooting = false;
	bool			_weaponChanged = false;
	int				_ammoPrice = 0;

	// Ammo
	int PistolAmmo = 0;
	int SmgAmmo = 0;
	int ShotgunAmmo = 0;
	int SniperAmmo = 0;
	int	currPistolAmmo = 0;
	int	currSmgAmmo = 0;
	int	currShotgunAmmo = 0;
	int	currSniperAmmo = 0;

	// Bullet
	vector<shared_ptr<GameObject>>	bullets;
	vector<shared_ptr<GameObject>>	gunObject;
	vector<shared_ptr<GameObject>>	muzzleFlashObject;
	Vec3							cameraPosForBullet;
	Vec3							cameraLookForBullet;
};

class Bullet : public Component
{
public:
	Bullet();
	virtual ~Bullet();

public:
	virtual void Update() override;

	BULLET_STATE GetState() { return _currState; };
	void SetState(BULLET_STATE state) { _currState = state; };

private:
	float			_lifeTime = 5.f;
	float			_currLifeTime = 5.f;
	BULLET_STATE	_currState = BULLET_STATE::LIVE;
	float			_speed = 2000.0f;
};

class MuzzleFlash : public Component
{
public:
	MuzzleFlash();
	virtual ~MuzzleFlash();
public:
	virtual void Update() override;

	MUZZLEFLASH_STATE GetState() { return _currState; };
	void SetState(MUZZLEFLASH_STATE state) { _currState = state; };

private:
	float			_lifeTime = 0.05f;
	float			_currLifeTime = 0.05f;
	MUZZLEFLASH_STATE	_currState = MUZZLEFLASH_STATE::LIVE;
};