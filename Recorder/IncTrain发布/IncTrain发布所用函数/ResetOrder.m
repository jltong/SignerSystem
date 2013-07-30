function [ClusterOrder,Num_of_Cluster,alpha,Mu,Variances]=ResetOrder(ClusterOrder,Num_of_Cluster,alpha,Mu,Variances)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    i=1;
    while i<=256&&i>0&&ClusterOrder(i)~=0
        while i<=256&&i>0&&ClusterOrder(i)~=i
             [Num_of_Cluster(ClusterOrder(i)),Num_of_Cluster(i)]=Exchange(Num_of_Cluster(ClusterOrder(i)),Num_of_Cluster(i));
             [alpha(ClusterOrder(i)),alpha(i)]=Exchange(alpha(ClusterOrder(i)),alpha(i));
             [Mu(:,ClusterOrder(i)),Mu(:,i)]=Exchange(Mu(:,ClusterOrder(i)),Mu(:,i));
             [Variances(:,ClusterOrder(i)),Variances(:,i)]=Exchange(Variances(:,ClusterOrder(i)),Variances(:,i));
             [ClusterOrder(ClusterOrder(i)),ClusterOrder(i)]=Exchange(ClusterOrder(ClusterOrder(i)),ClusterOrder(i));
        end
        i=i+1;
    end
end

