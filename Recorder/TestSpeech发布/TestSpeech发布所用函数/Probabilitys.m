function [  pro ] = Probabilitys(No_of_Cluster,No_of_Feature,X, alpha,Mu,Variances )
%返回每帧属于某个高斯模型的概率


[No_of_Feature,No_of_Data_Point]=size(X);
probability=zeros(No_of_Feature,No_of_Data_Point);
pro=zeros(No_of_Cluster,No_of_Data_Point);
%Variances=9*Variances./max(max(Variances));
%Mu=3*Mu./max(max(Mu));
%%%%%%%%%%%%%%%%%%%%%%%%%%%全方差
%for i=1:No_of_Cluster
%new=(X-repmat(Mu(:,i),1,No_of_Data_Point))'/Variances;
%Mah=sum(new.^2,2);
%Mah=Mah./(sum(Mah)/No_of_Data_Point);
%exph=exp(-0.5*Mah');
%exph=exph./(sum(exph)/No_of_Data_Point);
%Probability(:,i)=(2*pi)^(No_of_Feature/2)/abs(det(Variances))*exph';
%end
%Probability=Probability./repmat(max(Probability),No_of_Data_Point,1);
%pro=(Probability*alpha')';
%%%%%%%%%%%%%%%%%%%%%%%%%%%全方差

    sqrt2pi=1/sqrt(2*pi);
    for i=1:No_of_Cluster
        lamda=abs((X-repmat(Mu(:,i),1,No_of_Data_Point))./repmat(Variances(:,i),1,No_of_Data_Point));
         %%%%%%对lamda大小进行过滤
        lamdamax=max(lamda);
        for j=1:No_of_Data_Point
         if lamdamax(j)>=1110.5
             lamdamax(j)=0;
         else
             lamdamax(j)=1;
         end
        end
        lamda=exp(-(lamda.^2)/2);
        cov=repmat(Variances(:,i),1,No_of_Data_Point);
        probability=(lamda./cov)*sqrt2pi;
        pro(i,:)=prod(probability).*lamdamax;%%%%%%prod为列连乘
    end
            if(isfinite(max(max(pro)))==0)
                 %fprintf('增量学习中概率为NaN');
            end
end