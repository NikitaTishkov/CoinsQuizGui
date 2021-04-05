#include "city.h"
#include <time.h>
City::City(QPushButton *parent) : QPushButton(parent)
{

}

City::City(QPushButton *parent, int X, int Y, bool bIsCity)
    : QPushButton(parent),
      m_bIsCity(bIsCity)
{
    this->SetCoord(X, Y);
}

void City::SetCellParams(int X, int Y, bool bIsCity)
{
    this->m_Coord.SetX(X);
    this->m_Coord.SetY(Y);
    this->m_bIsCity = bIsCity;
}
/* -------------- */
void City::SetCoord(int xNew, int yNew)
{
    this->m_Coord.SetX(xNew);
    this->m_Coord.SetY(yNew);
}
void City::SetCoordX(int xNew)
{
    this->m_Coord.SetX(xNew);
}
void City::SetCoordY(int yNew)
{
    this->m_Coord.SetY(yNew);
}
Point City::GetCoord()
{
    return this->m_Coord;
}
/* -------------- */
void City::SetIsCity(bool bIsCityNew)
{
    this->m_bIsCity = bIsCityNew;
}
bool City::GetIsCity()
{
    return this->m_bIsCity;
}
/* -------------- */
void City::SetCountryID(int IDNew)
{
    this->m_iCountryID = IDNew;
}

int City::GetCoutnryID()
{
    return this->m_iCountryID;
}
/* Vault functions */
void City::IncreaseVaultVal(int ID, int iVal)
{
    this->m_aVault[ID] += iVal;
}

void City::DecreaseVaultVal(int ID, int iVal)
{
    this->m_aVault[ID] -= iVal;
}

void City::ChangeVaultVal(int ID, int iValNew)
{
    this->m_aVault[ID] = iValNew;
}

bool City::CheckVault()
{
    std::map<int, int>::iterator i;
    for(i = this->m_aVault.begin(); i != this->m_aVault.end(); ++i)
    {
        if(i->second <= 0)
            return false;
    }
    return true;
}

int City::GetForeignSum()
{
    int iForeignSum = 0;
    std::map<int, int>::iterator i;

    for(i = this->m_aVault.begin(); i != this->m_aVault.end(); ++i)
    {
        if(i->first != this->GetCoutnryID())
            iForeignSum += i->second;
    }
    return iForeignSum;
}

int City::GetVaultSum()
{
    int iSum = 0;
    std::map<int, int>::iterator i;

    for(i = this->m_aVault.begin(); i != this->m_aVault.end(); ++i)
    {
        iSum += i->second;
    }
    return iSum;
}
/* Checking if city is near to another */
bool City::IsNeighbourTo(City Neighb)
{
    if(Neighb.GetIsCity())
    {
        if(this->GetCoord().GetX() - 1 == Neighb.GetCoord().GetX() && this->GetCoord().GetY() == Neighb.GetCoord().GetY()) return true;
        if(this->GetCoord().GetX() + 1 == Neighb.GetCoord().GetX() && this->GetCoord().GetY() == Neighb.GetCoord().GetY()) return true;
        if(this->GetCoord().GetY() - 1 == Neighb.GetCoord().GetY() && this->GetCoord().GetX() == Neighb.GetCoord().GetX()) return true;
        if(this->GetCoord().GetY() + 1 == Neighb.GetCoord().GetY() && this->GetCoord().GetX() == Neighb.GetCoord().GetX()) return true;
    }
    return false;
}
/* Sending money between two cities */
void City::SendMoney(City *Neighb)
{
    for(int i = 1; i <= COINS_PER_DAY; i++)
    {
        double fChanceToSendForeign = static_cast<double>(this->GetForeignSum()) / this->GetVaultSum();
        double fSenForeignTreshold = static_cast <double>(rand()) / RAND_MAX;
        static bool bFlag = true;

        if((fChanceToSendForeign == 0 || fChanceToSendForeign < fSenForeignTreshold) &&
                this->m_aVault[this->GetCoutnryID()] > 0)
        {
            this->DecreaseVaultVal(this->GetCoutnryID(), 1);
            Neighb->IncreaseVaultVal(this->GetCoutnryID(), 1);

        }
        else
        {
            std::map<int, int>::iterator it;
            if(bFlag)
            {
                for(it = this->m_aVault.end(); it != this->m_aVault.begin(); --it)
                {
                    if(it->first != this->GetCoutnryID() && it->second > 0)
                    {
                        this->DecreaseVaultVal(it->first, 1);
                        Neighb->IncreaseVaultVal(it->first, 1);
                        break;
                    }
                }
                bFlag = !bFlag;
            }
            else
            {
                for(it = this->m_aVault.begin(); it != this->m_aVault.end(); ++it)
                {
                    if(it->first != this->GetCoutnryID() && it->second > 0)
                    {
                        this->DecreaseVaultVal(it->first, 1);
                        Neighb->IncreaseVaultVal(it->first, 1);
                        break;
                    }
                }
                bFlag = !bFlag;
            }
        }
    }
}
/* Illustrate data of City */
void City::UpdateCityInfo()
{
    QString WalletInfo = tr("ID: ") +
                         QString::number(this->GetCoutnryID()) + tr("\n");
    std::map<int, int>::iterator i;
    for(i = this->m_aVault.begin(); i != this->m_aVault.end(); ++i)
    {
        WalletInfo += tr("Wallet #") + QString::number(i->first) + tr(": ") + QString::number(i->second) + tr("\n");
    }

    this->setText(WalletInfo);
}
/* Checking if threre is all currancies in City wallet */
bool City::IsThereAllCurrsInCity(int iNum)
{
    if(this->m_aVault.size() == iNum)
        return true;

    return false;
}
