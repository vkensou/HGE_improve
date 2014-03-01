#include "..\..\include\hgeanim2.h"
#include <fstream>

//HGE *hgeAnimation2::hge=0;

int CAnimDate::LoadDate(const wchar_t* file)
{
	HGE *hge = hgeCreate(HGE_VERSION);
	void *dat;
	char *zz;
	int offset = 0;
	dat = hge->Resource_Load(file);
	zz = (char*)dat;
	if(!dat)return -1;
	int mn = 0,n = 0,mm = 0,m = 0;
	tagqp nqp;
	tagpge npg;
	tagfm nfm;
	tagfme nfme;
	tagan nan;

	memcpy(&mn, zz + offset, sizeof(mn));
	offset+=sizeof(mn);
	for(n = 0; n<mn;n++)
	{
		memcpy(&nqp, zz + offset, sizeof(nqp));
		offset+=sizeof(nqp);
		qps.push_back(nqp);
	}
	memcpy(&mn, zz + offset, sizeof(mn));
	offset+=sizeof(mn);
	for(n = 0; n<mn;n++)
	{
		nfm.qps.clear();
		memcpy(&mm, zz + offset, sizeof(mm));
		offset+=sizeof(mm);
		for(m = 0; m<mm;m++)
		{
			memcpy(&npg, zz + offset, sizeof(npg));
			offset+=sizeof(npg);
			npg.index--;
			nfm.qps.push_back(npg);
		}
		fms.push_back(nfm);
	}
	memcpy(&mn, zz + offset, sizeof(mn));
	offset+=sizeof(mn);
	for(n = 0; n<mn;n++)
	{
		nan.fms.clear();
		memcpy(&mm, zz + offset, sizeof(mm));
		offset+=sizeof(mm);
		for(m = 0; m<mm;m++)
		{
			memcpy(&nfme, zz + offset, sizeof(nfme));
			offset+=sizeof(nfme);
			nfme.index --;
			nan.fms.push_back(nfme);
		}
		memcpy(&nan.mode, zz + offset, sizeof(nan.mode));
		offset+=sizeof(nan.mode);
		ans.push_back(nan);
	}
	hge->Resource_Free(dat);
	hge->Release();
	return 0;
}

hgeAnimation2::hgeAnimation2()
{
	//hge=hgeCreate(HGE_VERSION);
	m_data = 0;
	spr = 0;
	spr = new hgeSprite2(0,0,0,0,0);
	bPlaying = false;
	m_anim = m_frame = m_frame2 = -1;
	m_z = 1.f;
}

void hgeAnimation2::Play()
{
	if(m_data && m_anim>=0 && m_anim<(int)m_data->ans.size() && m_data->ans[m_anim].fms.size() > 0)
	{
		bPlaying = true;
		m_frame = 0;
		m_frame2 = m_data->ans[m_anim].fms[m_frame].index;
		hgeTimer::StartTick();
	}
	else
	{
		m_anim = m_frame = m_frame2 = -1;
	}
}

void hgeAnimation2::Update(float fDeltaTime)
{
	if(!bPlaying)return ;
	if(hgeTimer::NowTick()>= m_data->ans[m_anim].fms[m_frame].time)
	{
		m_frame++;
		hgeTimer::StartTick();

		if(m_frame == m_data->ans[m_anim].fms.size())
		{
			switch(m_data->ans[m_anim].mode)
			{
			case 0:
				bPlaying = false;
				hgeTimer::StopTick();
				m_frame--;
				break;
			case 1:
				m_frame=0;
				break;
			}
		}
		m_frame2 = m_data->ans[m_anim].fms[m_frame].index;
	}
}

void hgeAnimation2::Render(float x,float y)
{
	if(m_frame2==-1)return ;
	//tagpge* pg;
	tagqp* qp;
	spr->SetZoom();
	float x1,y1,x2,y2;
	for(unsigned int i =0 ;i<m_data->fms[m_frame2].qps.size();i++)
	{
		qp = &(m_data->qps[m_data->fms[m_frame2].qps[i].index]);
		spr->SetTextureRect(qp->left ,qp->top ,qp->width ,qp->height );
		//spr->SetCenterPoint(qp->x,qp->y );
		spr->SetZoom(m_z,m_z);
		//spr->SetRenderPosition(x + m_z * ( (float)m_data->ans[m_anim].fms[m_frame].x + (float)m_data->fms[m_frame2].qps[i].x) ,y + m_z * ( (float)m_data->ans[m_anim].fms[m_frame].y + (float)m_data->fms[m_frame2].qps[i].y));
		x1 = m_anim==-1?0.f: (float)m_data->ans[m_anim].fms[m_frame].x;y1 = m_anim==-1?0.f: (float)m_data->ans[m_anim].fms[m_frame].y;
		x2 = (float)m_data->fms[m_frame2].qps[i].x;y2 = (float)m_data->fms[m_frame2].qps[i].y;
		spr->SetRenderPosition(x + m_z * ( x1 + x2 - qp->x) ,y + m_z * ( y1 + y2 - qp->y));
		spr->Render();
	}
}

void hgeAnimation2::RenderEx(float x,float y)
{
	if(m_frame2==-1)return ;
	//tagpge* pg;
	tagqp* qp;
	spr->SetZoom(-1.f,1.f);
	float x1,y1,x2,y2;
	for(unsigned int i =0 ;i<m_data->fms[m_frame2].qps.size();i++)
	{
		qp = &(m_data->qps[m_data->fms[m_frame2].qps[i].index]);
		spr->SetTextureRect(qp->left ,qp->top ,qp->width ,qp->height );
		spr->SetCenterPoint(qp->x,qp->y );
		spr->SetZoom(-m_z,m_z);
		x1 = m_anim==-1?0.f: (float)m_data->ans[m_anim].fms[m_frame].x;y1 = m_anim==-1?0.f: (float)m_data->ans[m_anim].fms[m_frame].y;
		x2 = (float)m_data->fms[m_frame2].qps[i].x;y2 = (float)m_data->fms[m_frame2].qps[i].y;
		spr->SetRenderPosition(x + m_z * ( x1 + x2 - qp->x) ,y + m_z * ( y1 + y2 - qp->y));
		//spr->SetRenderPosition(x + m_z * ( m_data->ans[m_anim].fms[m_frame].x + m_data->fms[m_frame2].qps[i].x) ,y + m_z * ( m_data->ans[m_anim].fms[m_frame].y + m_data->fms[m_frame2].qps[i].y));
		spr->Render();
	}
}

void hgeAnimation2::SetAnimData(CAnimDate* na)
{
	m_data = na;
	bPlaying = false;
	m_anim = m_frame = m_frame2 = -1;
	spr->SetTexture(m_data->tex);
}

void hgeAnimation2::SetAnim(int n)
{
	n--;
	if(m_data && (int)m_data->ans.size()>0 && n >=0 && n<(int)m_data->ans.size())
	{
		m_anim = n;
		m_frame = 0;
		m_frame2 = m_data->ans[m_anim].fms[m_frame].index;
	}
}

void hgeAnimation2::SetAnimFrame(int n)
{
	n--;
	if(!m_data)return;
	if(m_anim == -1)return ;
	if(m_data->ans[m_anim].fms.size()==0)return;
	if(n<0 || n>=(int)m_data->ans[m_anim].fms.size())return ;
	//if(n<0)n=0;
	//if(n>=m_data->ans[m_anim].fms.size())n=m_data->ans[m_anim].fms.size();
	m_frame = n;
	m_frame2 = m_data->ans[m_anim].fms[m_frame].index;
}

void hgeAnimation2::SetFrame(int n)
{
	n--;
	if(!m_data)return;
	if(n<0 || n>=(int)m_data->fms.size())return ;
	bPlaying = false;
	StopTick();
	m_anim = -1;
	m_frame = m_frame2 = n;
}

