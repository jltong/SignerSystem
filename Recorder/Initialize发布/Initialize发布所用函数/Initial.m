function [  ] = Initial(  )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
Max_Cluster=256;
MaxSpeaker=100;
dimension=40;
MU=zeros(dimension,Max_Cluster,MaxSpeaker);
VAR=MU;
ALPHA=zeros(Max_Cluster,MaxSpeaker);
Num_of_Cluster=zeros(Max_Cluster,1);
Num_of_Sample=zeros(Max_Cluster,MaxSpeaker);
No_of_speaker=0;
SpeakerName=repmat('          ',MaxSpeaker,1);
save('E:\Speechdata\speakerdata.mat','MU','ALPHA','VAR','No_of_speaker','SpeakerName','Num_of_Cluster','Num_of_Sample');
end

