#include "StdAfx.h"
#include "Users.h"
#include "ADOConn.h"

Users::Users(void)
{
	UserName="";
	PassWord="";
	
	UserId="";
	Dep="";
	Email="";
	TTA="";
	DTA="";
}

Users::Users(CString cUserName,CString cPassWord){
	this->UserName=cUserName;
	this->PassWord=cPassWord;
	
}
Users::Users(CString cUserName,CString cUserId,CString cDep,CString cEmail){
	this->UserName=cUserName;
	this->UserId=cUserId;
	this->Dep=cDep;
	this->Email=cEmail;
}

Users::~Users(void)
{
}
CString Users::getUserName(){
	return this->UserName;
}
CString Users::getPassWord(){
	return this->PassWord;
}
CString Users::getUserId(){
	return this->UserId;
}
CString Users::getDep(){
	return this->Dep;
}
CString Users::getEmail(){
	return this->Email;
}

CString Users::getTTA(){
	return this->TTA;
}
CString Users::getDTA(){
	return this->DTA;
}
void Users::setUserId(CString cUserId){
	this->UserId = cUserId;
}
void Users::setUserName(CString cUserName){
	this->UserName=cUserName;
}
void Users::setPassWord(CString cPassWord){
	this->PassWord=cPassWord;
}

void Users::setTTA(CString cTTA){
	this->TTA = cTTA;
}
void Users::setDTA(CString cDTA){
	this->DTA = cDTA;
}

BOOL Users::isExist(CString cUserName,CString cTableName){
		//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置SELECT语句
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM "+cTableName+" WHERE username='" + cUserName + "'");
	
	//执行SELECT语句
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);
	if (m_pRecordset->adoEOF){
		m_AdoConn.ExitConnect();
		return false;
	}
	else{
		m_AdoConn.ExitConnect();
		return true;
	}
}

int Users::isExistId(CString cUserId,CString cTableName){
		//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置SELECT语句
	_bstr_t vSQL;
	_RecordsetPtr m_pRecordset;
	
	vSQL = _T("SELECT * FROM "+cTableName+" WHERE userid='" + cUserId + "'");
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);
	if (m_pRecordset->adoEOF){
		m_AdoConn.ExitConnect();
		return 0;//该用户不存在，返回！
	}
	
	//计算目标项的序号！
	vSQL = _T("SELECT * FROM "+cTableName);
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);
	//执行SELECT语句
	
	int count = 0;
	while (!m_pRecordset->adoEOF){
		count++;
		CString id = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("userid");
		if(id == cUserId){
			m_AdoConn.ExitConnect();
			return count;
		}
		m_pRecordset->MoveNext();
	}

	//断开与数据库的连接
	
}

BOOL Users::Insert(){
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置INSERT语句
	
	_bstr_t vSQL;
	_RecordsetPtr m_pRecordset;

	vSQL = _T("INSERT INTO login(username,password) VALUES('" + this->UserName + "','" + this->PassWord + "')");	
	//执行INSERT语句
	BOOL outcome=m_AdoConn.ExecuteSQL(vSQL);	
	//m_pRecordset->Update();
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return outcome;
}
BOOL Users::InsertTrainInfo(){
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置INSERT语句
	
	_bstr_t vSQL;
	_RecordsetPtr m_pRecordset;
	

	vSQL = _T("INSERT INTO train(username,userid) VALUES('" + this->UserName + "','" + this->UserId +"')");	
	//执行INSERT语句
	BOOL outcome=m_AdoConn.ExecuteSQL(vSQL);	

	//m_pRecordset->Update();
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return outcome;

}

BOOL Users::InsertUserInfo(){
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置INSERT语句
	
	_bstr_t vSQL;
	_RecordsetPtr m_pRecordset;
	

	vSQL = _T("INSERT INTO userinfo(username,userid,department,email) VALUES('" + this->UserName + "','" + this->UserId + "','" + this->Dep + "','" + this->Email + "')");	
	//执行INSERT语句
	BOOL outcome=m_AdoConn.ExecuteSQL(vSQL);	

	//m_pRecordset->Update();
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return outcome;
}

BOOL Users::InsertSignIn(){
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置INSERT语句
	

	_bstr_t vSQL;
	//vSQL =_T("SELECT * FROM signin");
	//_RecordsetPtr m_pRecordset;
	//m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	vSQL = _T("INSERT INTO signin(username,userid,TimeToArrive,DateToArrive) VALUES('" + this->UserName + "','"+ this->UserId + "','"+ this->getTTA() +"','"+ this->getDTA() +"')");	
	//执行INSERT语句
	BOOL outcome=m_AdoConn.ExecuteSQL(vSQL);

	//m_pRecordset->Update();
	//when the consequence of the SELECT is empty,
	//the Update() may have memory access error.

	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return outcome;
}

void Users::UpdateInfo(CString cUserName,CString cUserId,CString cDep,CString cEmail){
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置UPDATE语句

	_bstr_t vSQL;
	/*
	vSQL =_T("SELECT * FROM userinfo");
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);
	*/
	vSQL = _T("UPDATE userinfo SET UserName='" + cUserName + "',Department='"+ cDep +"',Email='"+ cEmail +"' WHERE UserId='" + cUserId + "'");
	//执行UPDATE语句
	m_AdoConn.ExecuteSQL(vSQL);
	//m_pRecordset->Update();
	m_AdoConn.ExitConnect();
}

void Users::UpdatePwd(CString cUserName,CString cPassWord){
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置UPDATE语句

	_bstr_t vSQL;
	vSQL = _T("UPDATE Users SET PassWord='" + cPassWord + "' WHERE UserName='" + cUserName + "'");
	//执行UPDATE语句
	m_AdoConn.ExecuteSQL(vSQL);	
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
}

void Users::Delete(CString cUserName){
		//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置DELETE语句
	_bstr_t vSQL;
	vSQL = _T("DELETE FROM login WHERE UserName='" + cUserName	+ "'");
	//执行DELETE语句
	m_AdoConn.ExecuteSQL(vSQL);	
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
}

//根据员工编号读取所有字段值
void Users::GetInfo(CString cUserName)
{
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置SELECT语句
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM login WHERE username='" + cUserName + "'");
	//执行SELETE语句
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	//返回各列的值
	if (!m_pRecordset->adoEOF)
	{
		this->UserName = cUserName;
		this->PassWord = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("PassWord");
	}
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
}


BOOL Users::GetUserInfo(CString cUserName)
{
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置SELECT语句
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM userinfo WHERE UserName ='" + cUserName + "'");
	//执行SELETE语句
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	//返回各列的值
	if (!m_pRecordset->adoEOF)
	{
		this->UserName = cUserName;
		this->UserId = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("UserId");
		this->Dep = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("DepartMent");
		this->Email =(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("Email");
		return TRUE;
	}
	else{
		return FALSE;
	}
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
}