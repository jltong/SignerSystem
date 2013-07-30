function [ output ] = sgn( input )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
[a,b]=size(input);
for i=1:a
    for j=1:b
        if input(i,j)>=0
            input(i,j)=1;
        else
          input(i,j)=-1;  
        end
    end
end
output=zeros(a,b);
for i=1:b-1
    output(:,i)=abs(input(:,i+1)-input(:,i))/2;
end
output=sum(output,2);
end

