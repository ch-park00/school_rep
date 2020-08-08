%%
function xhpf=HPF(u)

persistent prevX
persistent prevU
persistent dt tau
persistent firstrun

if isempty(firstrun)
    prevX=0;
    prevU=0;
    dt=0.01;
    tau=0.0233;
    firstrun=1;
end

alpha=tau/(tau+dt);
xhpf=alpha*prevX+alpha*(u-prevU);

prevX=xhpf;
prevU=u;



