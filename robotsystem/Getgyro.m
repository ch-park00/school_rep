function [p q r]=Getgyro()

persistent wx wy wz
persistent k firstrun

if isempty(firstrun)
    load ArsGyro
    k=1;
    firstrun=1;
end
p=wx(k);
q=wy(k);
r=wz(k);
k=k+1;