function [ Wavx1, fs ] = readspeech (speechname ,SpeakerName ,addr)
%ww=struct2cell('E:\34trainsample\1');
%cd('E:\34trainsample\1');


cd(addr);%addr='E:\Speechdata';
SpeakerName=[addr,'\',SpeakerName];%SpeakerName='E:\Speechdata\Test'
cd(SpeakerName);
speechname=[SpeakerName,'\',speechname];
[Wavx1,fs,bits]=wavread(speechname);     % ���������ļ���*.wav��   

%sound(Wavx1,fs);
return;
end
