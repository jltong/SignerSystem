
function [mfccc,FrameSize,framelocation,energy]=getmfcc(speechname,SpeakerName,dimension)%对某一个文件夹的某一个文件进行提取mfcc参数。返回mfcc参数ccc,帧数sizec，
%提取特征参数，得到模型训练所需的点
%direct从第几个目录读取数据
%start 从目录中第几个文件读取
%filenum读取文件数目
%snr没用到
%dimension生成数据维数
%energy 滤波能量
%framelocation 每个语音段所提取的点个数
%FrameSize所提取的点个数
%mfccc提取出来的点
bankm=24;
addr='E:\Speechdata';
%addr='E:\34trainsample';
framelength=256;
maxfrequency=8000;
framelocation=0;
%xx=zeros(75000,256);
index=0;
xxt=zeros(700,framelength);

    [wavx ,fs ]=readspeech(speechname,SpeakerName,addr);%读目录addr第i个目录的第j个文件
    x=0.3*wavx;
    xtemp=double(x);
    xxtemp=enframe(xtemp,framelength,framelength/2);% 语音信号分帧  对x 256点分为一帧 按行存储
    xxtempE=xxtemp.^2;
    xxtempEn=sum(xxtempE,2);
    [xxtempEna,xxtempEnb]=size(xxtempEn);
    xxtempEm=mean(xxtempEn)/4;
    xxtempEm=repmat(xxtempEm,xxtempEna,xxtempEnb);
    xxtempEn=xxtempEn-xxtempEm;%短时能量高
    xxtempZ=sgn(xxtemp);
    xxtempzm=mean(xxtempZ);
    [xxtempZa,xxtempZb]=size(xxtempZ);
    xxtempzm=repmat(xxtempzm,xxtempZa,xxtempZb);
    xxtempZ=xxtempZ-xxtempzm*2;%短时过零率低
    [xline,xrow]=size(xxtemp);
    Discard=0;
    j=1;
    while  j+Discard<xline %将短时过零率高  短时能量低的帧舍弃
        if xxtempEn(j)<0 && xxtempzm(j)>0
            temp=xxtemp(j,:);
            while xxtempEn(xline-Discard)<0 && xxtempZ(xline-Discard)>0
                Discard=Discard+1;
            end
            xxtemp(j,:)=xxtemp(xline-Discard,:);
            xxtemp(xline-Discard,:)=temp;
            xteEn=xxtempEn(j);
            xxtempEn(j)=xxtempEn(xline-Discard);
            xxtempEn(xline-Discard)=xteEn;
            xtezm=xxtempZ(j);
            xxtempZ(j)=xxtempZ(xline-Discard);
            xxtempZ(xline-Discard)=xtezm;
            Discard=Discard+1;
        end
        j=j+1;
    end
    xxt((index+1):(index+xline-Discard),:)=xxtemp(1:xline-Discard,:);
    index=index+xline-Discard;
    xx=xxt(1:index,:);
%%%制作mel滤波器
%%%%%%%%%%%%%%%%%%%%%%%%%%%
melhigh=1127*log(1+maxfrequency/700);
e=2.718281828459045;
each=melhigh/bankm;
eachmel=zeros(1,bankm);
eachhz=zeros(1,bankm);
for i=1:bankm
    eachmel(i)=each*i;
    eachhz(i)=700*(e^(eachmel(i)/1127)-1);
    eachhz(i)=eachhz(i)*framelength/maxfrequency;
end

hz=zeros(bankm+1);
hz(2:bankm+1)=eachhz(1:bankm);
bank=zeros(framelength,bankm);
for i=1:bankm
    for j=1:framelength
        if(j<=hz(i)&&j>hz(i-1))
            bank(j,i)=(j-hz(i-1))/(hz(i)-hz(i-1));
        end
        if(j<=hz(i+1)&&j>hz(i))
            bank(j,i)=(hz(i+1)-j)/(hz(i+1)-hz(i));
        end
        if (j>hz(i+1))
            bank(j,i)=0;
        end
    end
end
% 归一化mel滤波器组系数
[banka,bankb]=size(bank);
bank=full(bank);%24*102
bank=bank/max(bank(:));
bankS=sum(bank);
bank=bank./repmat(bankS,banka,1);
bank=bank';
[bankline,bankrow]=size(bank);
dctcoef=zeros(dimension/2,bankm);
for k=1:dimension/2
    for n=1:bankm
        dctcoef(k,n)=cos((n-0.5)*k*pi/(bankm));%每行为一维MFCC的余弦参数
        if(abs(dctcoef(k,n))<0.01)
            dctcoef(k,n)=0;
        end
    end
end
% 归一化倒谱提升窗口
w = 1 + (dimension/4) * sin(pi * (1:dimension/2) /(dimension/2));
w = w/max(w);
FrameSize=0;
c0=zeros(size(xx,1),bankline);
m=zeros(size(xx,1),dimension/2);
%%%%%%%%%%%%%%%%%%%%%%%%%%去掉平方，以mel滤波后的能量计算
for i=1:size(xx,1)% 计算每帧的MFCC参数
    y = xx(i,:);%取其中一帧
    s1=y';
    s2 = y' .* hamming(framelength);
    t1 = real(fft(s1));%快速傅里叶变换t：256*1
    t1=abs(t1);
%     t2=real(fft(s2));
%     t2=abs(t2);
    t2=abs(fft(s2));
    t2=(t2).^2;
    c0(i,:)=bank*t1(1:bankrow);
    ct2=bank*t2(1:bankrow);
    c1=dctcoef*log(ct2);
    c2 = c1.*w';
    m(i,:)=c2';
    FrameSize=FrameSize+1;
end
energy=mean(c0(1:FrameSize,:));
dtm = zeros(size(m));
for i=3:size(m,1)-2
    dtm(i,:) = -m(i+1,:) - m(i-1,:);%求取1阶差分系数  %dtm(i,:) = -2*m(i-2,:) - m(i-1,:) + m(i+1,:) + 2*m(i+2,:);%求取2阶差分系数
end
dtm = dtm / 2;%dtm = dtm / 10;
ccc = [m dtm];%合并mfcc参数和一阶差分mfcc参数
ccc = ccc(3:size(m,1)-2,:);%去除首尾两帧，因为这两帧的一阶差分参数为0
FrameSize=FrameSize-4;
ccc=ccc';
w=ones(dimension,FrameSize);
for wi= 1:(dimension/2)
    w(wi,:)=0.3+0.7*cos(wi*pi/(dimension/2));
end
mfccc=ccc;

end

