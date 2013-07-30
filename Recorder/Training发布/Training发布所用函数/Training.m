function [ ] = Training(SpkName,SphName,trainnum)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
%SpeakerName 以10位或更长的字符，表示所训练说话人的名字
%SphName 以行存储的待训练的语音名，每行必须有相同字符个数，不足则以空格补足
addpath('E:\Speechdata');
dimension=40;%%%%%%%%%%%端点检测 短时能量高  短时过零率低的为浊音，必须是偶数
Max_Cluster=256;
framelength=256;
confidence=0.1;
Cluster=50;%每个模型聚类数
S=load('E:\Speechdata\speakerdata.mat','MU','ALPHA','VAR','No_of_speaker','SpeakerName','Num_of_Cluster','Num_of_Sample');
ALPHA=S.ALPHA;
MU=S.MU;
VAR=S.VAR;
No_of_speaker=S.No_of_speaker;
SpeakerName=S.SpeakerName;
Num_of_Cluster=S.Num_of_Cluster;
Num_of_Sample=S.Num_of_Sample;
No_of_speaker=No_of_speaker+1;
speakeradd=No_of_speaker;
[Spka,Spkb]=size(SpkName);
SpeakerName(speakeradd,1:Spkb)=SpkName;
%对SpeakerName去括号
%[sa,sb]=size(SpeakerName);
% j=1;
% for i=1:Spklength
%     if SpkName(i)~=' '
%         SName(j)=SpkName(i);
%         j=j+1;
%     end
% end
[SphNum,Sphrow]=size(SphName);
Sample=0;
for i=1:SphNum
    [mfca,FrameSize,framenum,m]=getmfcc(SphName(i,:),SpkName,dimension);%第i个说话人
    if i==1
        mfc=mfca;
        Sample=Sample+FrameSize;
    else
        mfc=[mfc,mfca];
        Sample=Sample+FrameSize;
    end
end

fprintf('Add a new speaker: %s\n',SpkName);
[alpha,Mu,Variances]=GmmTraining(mfc,Cluster,0.0001,trainnum);
[alpharow,sizealpha]=size(alpha);
Num_Cluster=sizealpha;
Num_Sample=alpha*Sample;


[alphaa,alphab]=size(alpha);
Num_of_Sample(1:alphab,speakeradd)=Num_Sample';
Num_of_Cluster(speakeradd)=Num_Cluster;
ALPHA(1:alphab,speakeradd)=alpha';
MU(:,1:alphab,speakeradd)=Mu;
VAR(:,1:alphab,speakeradd)=Variances;
save('E:\Speechdata\speakerdata.mat','MU','ALPHA','VAR','No_of_speaker','SpeakerName','Num_of_Cluster','Num_of_Sample');



end

