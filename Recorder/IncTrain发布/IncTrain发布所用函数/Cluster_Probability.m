% Function to compute the Cluster Probablity
function [PC,INDEX] = Cluster_Probability(Data,Mu)%返回PC：每个聚类中点的个数，INDEX：每个点属于第几个聚类
[No_of_Features_within_Data,No_of_Data_Points] = size(Data);%数据和均值按列存储
[No_of_Features_within_Mu,No_of_Mu_Points] = size(Mu);
PC(1:No_of_Mu_Points) = 0;
INDEX(1:No_of_Data_Points) = 0;
Distance(1:No_of_Data_Points,1:No_of_Mu_Points) = 0.0;

for i=1:No_of_Data_Points
    for j = 1:No_of_Mu_Points
        Distance(i,j) = sqrt(dot(Data(:,i)-Mu(:,j),Data(:,i)-Mu(:,j)));%数据点i到聚类中心j的距离
    end
end

for i=1:No_of_Data_Points
    [value,idx] = min(Distance(i,:));
    PC(idx) = PC(idx)+1;
    INDEX(i) = idx;
end
PC = PC/No_of_Data_Points;