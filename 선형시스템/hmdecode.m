function origin_m=hmdecode(v,P) 
H=[P;eye(3)];
H_=gf(H);
N=length(v)/7;
origin_m=[];
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
origin_m=double(origin_m.x+0);
end
