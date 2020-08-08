%%
function [ax ay az]=GetAccel()

persistent fx fy fz
persistent k firstrun

if isempty(firstrun)
    load ArsAccel
    k=1;
    
    firstrun=1;
end

ax=fx(k);
ay=fy(k);
az=fz(k);
k=k+1;

end