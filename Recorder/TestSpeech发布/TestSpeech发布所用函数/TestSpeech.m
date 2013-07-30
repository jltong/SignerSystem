function [ pytest] = TestSpeech( SpeechName)

S=load('E:\Speechdata\speakerdata.mat','MU','ALPHA','VAR','No_of_speaker','SpeakerName','Num_of_Cluster','Num_of_Sample');
ALPHA=S.ALPHA;
MU=S.MU;
VAR=S.VAR;
No_of_Speaker=S.No_of_speaker;
SpeakerName=S.SpeakerName;
Num_of_Cluster=S.Num_of_Cluster;
Num_of_Sample=S.Num_of_Sample;



likelihoodlimit=0.1;
bankm=24;
[speechnum,speechwidth]=size(SpeechName);
[dimension,Clustermax,MaxSpeaker]=size(MU);
[Max_Speaker,Namewidth]=size(SpeakerName);
testname='Test';
for tests=1:speechnum
    speechname=SpeechName(1,:);
    [mfc,FrameSize,framenum,m]=getmfcc(speechname,testname,dimension);
    PY=zeros(speechnum,No_of_Speaker);
    for n=1:No_of_Speaker%将每秒语音分别计算置信度，
        X(:,1:FrameSize)=mfc(:,1:FrameSize);
        [No_of_Feature,No_of_Data_point]=size(X);
        pro=Probabilitys(Num_of_Cluster(n),No_of_Feature,mfc,ALPHA(:,n)',MU(:,:,n),VAR(:,:,n));
        prob=sum(pro.*repmat(ALPHA(1:Num_of_Cluster(n),n),1,No_of_Data_point));
        PX (:,n)=prob';
    end
    PX=PX./repmat(max(PX,[],2),1,No_of_Speaker);
    PXsum=zeros(FrameSize);
    PXmax=zeros(FrameSize);
    PXT=PX';
    [PXa,PXb]=size(PXT);
    if PXa==1
        PXsum=PXT;
        PXmax=PXT;
    else    
        PXsum=sum(PXT);%%计算帧置信度
        PXmax=max(PXT);
    end
    

    PXF=PXmax./PXsum;%置信度
    j=0;
    for k=1:FrameSize %将似然度低的帧置后
        if(PXF(k)<likelihoodlimit)
            PXF(k)=0;
            Ptemp=PXT(:,FrameSize-j);
            PXT(:,FrameSize-j)=PXT(:,k);
            PXT(:,k)=Ptemp;
            j=j+1;
        end
    end
    if FrameSize-j==0
        fprintf('帧似然度太低');
    end
    PXM=zeros(No_of_Speaker,FrameSize-j);
    PXM(:,:)=PXT(:,1:FrameSize-j);%去掉多重识别
    [PXMmax,PXrow]=max(PXM);%PXMmax为每列最大值。PXrow为最大值所在的列的标号，即每帧的候选说话人
    PXtabu=tabulate(PXrow);%统计出现最多次数的候选说话人
    PXtwo=PXtabu(:,2);
    [PXtwomax,PXtwomaxrow]=max(PXtwo);
    [PXMa,PXMb]=size(PXM);
    if PXMa==1
        PXrow=PXM;
    end
    
    for h=1:(FrameSize-j)%改
        if(PXrow(h)~=PXtwomaxrow)
            PXM(:,h)=0;
        end
    end

    PY=sum(PXM(:,1:FrameSize-j)');
    [pymax,pyadd]=max(PY,[],2);%pymax为每行最大值，pyadd为每行最大值位置
    pyspeaker=pyadd;
    
    pytest=SpeakerName(pyspeaker,:);
    
    fprintf('The  speech: "%s" test result is "%s".\n',SpeechName(tests,:),SpeakerName(pyspeaker,:));
end

end

