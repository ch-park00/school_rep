%% 메세지를 부호로 만듦.
m=[1 0 1 1 0 0 1 1 0 1 0 0];
G=[1 0 0 0 0 1 1;
   0 1 0 0 1 1 1;
   0 0 1 0 1 1 0;
   0 0 0 1 1 0 1];
%gf=2일때 0으로 만들어줌.즉, 0과 1로 구성되도록 만듦.
G_=gf(G);
N=length(m);
result=[];
for i=1:N/4
   
    
        temp=m((i-1)*4+1:1:(i-1)*4+4);
        temp=gf(temp);
        temp1=temp*G_;
        result=[result temp1];
end
disp(char(result.x+'0'))

%% 복구

v=[1 0 1 1 0 1 1];
H=[0 1 1;1 1 1;1 1 0;1 0 1;1 0 0;0 1 0;0 0 1];
v_=gf(v);
H_=gf(H);
s=v_*H_;
dec=0;
for i=1:7
   if s==H_(i,:)
      dec=i; 
   end
end
if dec~=0
   v_(dec)=v_(dec)+1; 
end
    


%%

v=[1 0 0 1 1 0 1 1 1 1 0 1 1 1 0 1 1 0 0 1 0];
H=[0 1 1;1 1 1;1 1 0;1 0 1;1 0 0;0 1 0;0 0 1];
H_=gf(H);
N=length(v)/7;
origin_m=[];

temp=[];
for i=1:N
   m=v((i-1)*7+1:1:(i-1)*7+7);
   m_=gf(m);
   s=m_*H_;
   errorbit=0;
   for j=1:7
      if s==H_(j,:)
          errorbit=j;
      end
   end
   if errorbit~=0
      m_(errorbit)=m_(errorbit)+1; 
   end
   origin_m=[origin_m m_(1:4)];
end