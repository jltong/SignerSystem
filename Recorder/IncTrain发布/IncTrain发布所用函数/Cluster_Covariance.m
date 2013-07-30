%Co-variance Computation for a Cluster
function [COVAR] = Cluster_Covariance(Data,IDX,No_of_Cluster)
index=1;
[a,b]=size(Data);
COVAR=zeros(a,No_of_Cluster);
for i=1:No_of_Cluster
    temp=zeros(b,a);
    index=1;
    indexold=index;
    for j=1:b
        if(IDX(j)==i)
            temp(index,:)=Data(:,j)';
            index=index+1;
        end
    end
    %tempt=zeros(index,a);
    tempt=temp(indexold:index-1,:);
    COVAR(:,i)=(var(tempt))';

end
COVAR=sqrt(COVAR);
    %for i=1:No_of_Cluster
      %  for j=1:a
        %  if(COVAR(j,i)<0.1)
         % COVAR(j,i)=0.1;
         % end
        %end
    %end
end
