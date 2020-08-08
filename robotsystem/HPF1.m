function xhpf=HPF1(u)

persistent prevX
persistent prevU
persistent dt tau
persistent firstrun1

if isempty(firstrun1)
    prevX=0;
    prevU=0;
    dt=0.01;
    tau=0.01;
    firstrun1=1;
end

alpha=tau/(tau+dt);
xhpf=alpha*prevX+alpha*(u-prevU);

prevX=xhpf;
prevU=u;