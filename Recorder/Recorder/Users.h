#if !defined(AFX_USERS_H__451F3215_5B38_48AF_8D6D_A4361016F23E__INCLUDED_)
#define AFX_USERS_H__451F3215_5B38_48AF_8D6D_A4361016F23E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class Users
{
	//现在只设置两个属性，诸如用户权限TypeofUsers等属性等框架搭好后再完善
private:
	CString UserName;
	CString PassWord;
	CString UserId;
	CString Dep;//department
	CString Email;
	//CString UserType;
	CString TTA;
	CString DTA;
public:
	Users(void);
	Users(CString cUserName,CString cPassWord);//login user!
	Users(CString cUserName,CString cUserId,CString cDep,CString cEmail);//info submission user!
	~Users(void);

	CString getUserName();
	CString getPassWord();
	CString getUserId();
	CString getDep();
	CString getEmail();
	//CString getUserType();
	CString getTTA();
	CString getDTA();
	void setTTA(CString cTTA);
	void setDTA(CString cDTA);
	void setUserName(CString cUserName);
	void setUserId(CString cUserId);
	void setPassWord(CString cPassWord);
	//void setUserType(CString cUserType);

	//database operation in sql
	BOOL isExist(CString cUserName,CString cTableName);//判断用户名是否存在
	int isExistId(CString cUserId,CString cTableName);//判断用户ID是否存在
	BOOL Insert();
	BOOL InsertUserInfo(); 
	BOOL InsertTrainInfo(); 
	BOOL InsertSignIn(); 
	void UpdateInfo(CString cUserName,CString cUserId,CString cDep,CString cEmail);
	void UpdatePwd(CString cUserName,CString cPassWord);
	void Delete(CString cUserName);
	
	//用cUserName的信息更新对象信息
	void GetInfo(CString cUserName);
	BOOL GetUserInfo(CString cUserName);

};
#endif // !defined(AFX_USERS_H__451F3215_5B38_48AF_8D6D_A4361016F23E__INCLUDED_) end
