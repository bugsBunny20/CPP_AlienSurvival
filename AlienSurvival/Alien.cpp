#include "Alien.h"
#include "Data.h"
#include <iostream>
#include "GameManager.h"

Alien::Alien(int id, int health, int energy, int damagePower) :
	_id(id),
	_health(health),
	_energy(energy),
	_energyMultiplerForRun(2),
	_damagePower(damagePower),
	_currentState(AlienState::Walk),
	_isSheltered(false),
	_range(3),
	_moveSpeed(10),
	_numberOfDirections(4)
{
	SetCurrentDirection();
}

bool Alien::ShouldAttack()
{
	if (_isShelterInRange && _health < _minHealth)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Alien::~Alien()
{
}

void Alien::GatherResources(std::weak_ptr<Resource> resource)
{
	shared_ptr<Resource> sharedResource = resource.lock();
	if (sharedResource!=nullptr)
	{
		_ownedResources.push_back(resource);
		sharedResource->SetIsOwned(true);
	}
	else
	{
		SetCurrentState(AlienState::Walk);
	}
}

void Alien::SetPosition(Position pos)
{
	_pos = pos;
}

Position Alien::GetPosition()
{
	return _pos;
}

Position Alien::GetNewPosition(int maxX,int maxY)
{
	Position newPosition = _pos;
	switch (_currentDirection)
	{
	case Direction::South:
	case Direction::North:
		newPosition = { _pos.x, _pos.y + _moveSpeed * GetCurrentDirection()};
		break;
	case Direction::East:
	case Direction::West:
		newPosition = { _pos.x + _moveSpeed * GetCurrentDirection(), _pos.y};
		break;
	}
	newPosition.x = ClampValue(newPosition.x, 0, maxX);
	newPosition.y = ClampValue(newPosition.y, 0, maxY);

	return newPosition;
}

int Alien::ClampValue(int value, int minSize, int maxSize)
{
	int difference;
	if (value > maxSize) 
	{
		RevertCurrentDirection();
		difference = value - maxSize;
		value = maxSize - difference;
	}
	if (value < minSize)
	{
		RevertCurrentDirection();
		value = abs(value);
		if (value > maxSize) {
			value = ClampValue(value, minSize, maxSize);
		}
	}
	return value;
}

int Alien::GetSpeed()
{
	return _moveSpeed;
}

void Alien::RevertCurrentDirection()
{
	switch (_currentDirection)
	{
	case Direction::South:
		_currentDirection = Direction::North;
		break;
	case Direction::North:
		_currentDirection = Direction::South;
		break;
	case Direction::East:
		_currentDirection = Direction::West;
		break;
	case Direction::West:
		_currentDirection = Direction::East;
		break;
	}
}

void Alien::SetIsShelterInRange(bool isShelterInRange)
{
	_isShelterInRange = isShelterInRange;
}

int Alien::GetCurrentDirection()
{
	switch (_currentDirection)
	{
	case Direction::South:
		return -1;
	case Direction::North:
		return 1;
	case Direction::East:
		return 1;
	case Direction::West:
		return -1;
	default:
		return 1;
	}
}

void Alien::SetCurrentDirection()
{

	int randomSeed = (rand() % _numberOfDirections);
	_currentDirection = static_cast<Direction>(randomSeed);
}

int Alien::GetRange()
{
	return _range;
}

void Alien::ConsumeEnergy(int energyConsumed)
{
	if (IsAlive())
	{
		_energy -= energyConsumed;
		if (_energy <= 0 && !IsSheltered())
		{
			_energy = 0;
			_currentState = AlienState::Dead;
		}
	}
}

void Alien::RunToShelter(shared_ptr<Shelter> shelter)
{
	if (shelter != nullptr) 
	{
		ConsumeEnergy(_energy * _energyMultiplerForRun);
		if (!shelter->GetIsOccupied())
		{
			Regenerate();
			shelter->SetIsOccupied(true);
		}
	}
}

void Alien::Regenerate()
{
	int energyNeeded = _maxEnergy - _energy;
	int healthNeeded = _maxHealth - _health;
	if (_ownedResources.size() > 0) {
		for (int i = 0; i < _ownedResources.size(); i++)
		{
			if (_energy < _maxEnergy)
			{
				shared_ptr<Resource> consumableResource = _ownedResources[i].lock();
				if (consumableResource->GetIsActive())
				{
					int energyInResource = consumableResource->GetResourceEnergy();
					if (energyInResource < energyNeeded)
					{
						_energy += energyInResource;
					}
					else
					{
						_energy += energyNeeded;
						energyInResource -= energyNeeded;
					}
					consumableResource->ResourceAmountConsumed(energyInResource);
					if (consumableResource->GetResourceEnergy() == 0)
					{
						_ownedResources.erase(_ownedResources.begin() + i);
						consumableResource->SetIsOwned(false);
						break;
					}
				}
			}
			if (_health < 100)
			{
				shared_ptr<Resource> consumableResource = _ownedResources[i].lock();
				if (consumableResource->GetIsActive())
				{
					int energyInResource = consumableResource->GetResourceEnergy();
					if (energyInResource < healthNeeded)
					{
						_health += energyInResource;
					}
					else
					{
						_health += healthNeeded;
						energyInResource -= healthNeeded;
					}
					consumableResource->ResourceAmountConsumed(energyInResource);
					if (consumableResource->GetResourceEnergy() == 0)
					{
						_ownedResources.erase(_ownedResources.begin() + i);
						consumableResource->SetIsOwned(false);
					}
				}
			}
		}
	}
}

void Alien::SetCurrentState(AlienState currentState)
{
	_currentState = currentState;
}

AlienState Alien::GetAlienState()
{
	return _currentState;
}

void Alien::Attack(shared_ptr<Alien> targetAlien)
{
	shared_ptr<Shelter> shelter = GameManager::GetInstance()->GetShelterFromGrid(_pos, _range).lock();
	SetIsShelterInRange(shelter != nullptr);

	if (ShouldAttack())
	{
		if (targetAlien->IsAlive() && !targetAlien->IsSheltered())
		{
			targetAlien->TakeDamage(_damagePower);
			ConsumeEnergy(_damagePower / 2);
		}
		else
		{
			SetCurrentState(AlienState::Walk);
		}
	}
	else
	{
		SetCurrentState(AlienState::Run);
		shared_ptr<Shelter> shelter = GameManager::GetInstance()->GetShelterFromGrid(_pos, _range).lock();
		RunToShelter(shelter);
	}
}

void Alien::TakeDamage(int damage)
{
	shared_ptr<Shelter> shelter = GameManager::GetInstance()->GetShelterFromGrid(_pos, _range).lock();
	SetIsShelterInRange(shelter != nullptr);

	if (ShouldAttack())
	{
		_health -= damage;
		if (_health <= 0 && !IsSheltered())
		{
			_currentState = AlienState::Dead;
		}
	}
	else
	{
		RunToShelter(shelter);
	}
}

bool Alien::IsSheltered()
{
	return _isSheltered;
}

bool Alien::IsAlive()
{
	return !(_currentState == AlienState::Dead);
}

void Alien::DisplayStatus()
{
	std::cout << " Alien" << _id << ": Health (" << _health << ") | Energy (" << _energy << ") | Pos (" << _pos.x << "," << _pos.y << ")" << "| Total owned : "<< _ownedResources.size() << std::endl;
}
