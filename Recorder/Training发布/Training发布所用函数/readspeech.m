function [Wavx1,fs] = readspeech(speechname,SpeakerName,addr)
%ww=struct2cell('E:\34trainsample\1');
%cd('E:\34trainsample\1');


cd(addr);
SpeakerName=[addr,'\',SpeakerName];
cd(SpeakerName);
speechname=[SpeakerName,'\',speechname];
[Wavx1,fs,bits]=wavread(speechname);% ���������ļ���*.wav�� 
%Wavx1: the sampled data    
%fs: the sample rate
%bits: the number of bits per sample

%sound(Wavx1,fs);
return;
end
