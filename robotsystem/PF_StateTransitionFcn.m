%%
function xNext=PF_StateTransitionFcn(x,u)

xNext=x;
xNext(1,:)=bsxfun(@times,x(1,:),-x(2,:))+x(3,:)*u;

xNext=xNext+bsxfun(@times,[1;1e-2;1e-1],randn(size(xNext)));
end