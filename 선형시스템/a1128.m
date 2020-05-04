%% image 읽어오기
s=[];
M=27;
icol=92;irow=112;
N=icol*irow;

for i=1:M
   img=imread(['C:\Users\chpark\Documents\MATLAB\PCA\database\training\' num2str(i,'%03g') '.bmp']);
   img=img(:,:,1);
   temp=reshape(img',N,1);
   temp=double(temp);
   s=[s temp];
end
%% 얼굴의 평균 분산 구하고 표준화(-128~128의 값으로 분포)시키기
X=zeros(N,M);
for i=1:M
   temp=s(:,i);
   m=mean(temp);
   st=std(temp);
   Z=(temp-m)/st;
   X(:,i)=Z*128+128; %s=128+128*z
   
end
%이미지 출력
figure(2);
for i=1:M
   img=reshape(X(:,i),icol,irow);
   img=uint8(img');
   subplot(ceil(sqrt(M)),ceil(sqrt(M)),i);
   imshow(img);
end
%% 얼굴 평균 구하기
m=mean(X,2);
img=reshape(m,icol,irow);
img=uint8(img');
 figure(3);
 imshow(img);
 title('평균 얼굴','fontsize',12);
%A가 평균의 데이터
A=zeros(N,M);
for i=1:M
   A(:,i)=double(X(:,i))-m; 
end

%% 공분산행렬 구하고 eigenvector와 eigenvalue구하기
%10304개의 eigenvalue가 나온다.-->계산량이 너무 많으므로 변형
L=A'*A/(M-1);
[v,lamda]=eig(L);

[lamda,index]=sort(lamda);
vtemp=zeros(size(v));
len=length(index);
for i=1:len
    vtemp(:,i)=v(:,len+1-index(i));
end
V=vtemp;
%U=A*v_i
U=[];
for i=1:size(V,2)
   U=[U (A*V(:,i))];
end

U_norm=[];
for i=1:size(U,2)
   U_norm(:,i)=U(:,i)./norm(U(:,i)); 
end

%%

 figure(4);
 for i=1:size(U_norm,2)
    img=reshape(U_norm(:,i),icol,irow);
    img=img';
    img=histeq(img,255);
    subplot(ceil(sqrt(M)),ceil(sqrt(M)),i);
    imshow(img);
 end

%% 
omega=[];
for h=1:size(A,2)
   ww=[];
   for i=1:size(U_norm,2)
      weightofimage=dot(A(:,h),U_norm(:,i));
      ww=[ww;weightofimage];
   end
   omega=[omega ww];
end

%%
cnt=0;
for zz=1:M

    %Inputimage=input('인식할 얼굴의 번호를 입력하세요\n');
Inputimage=imread(['C:\Users\chpark\Documents\MATLAB\PCA\database\test\' num2str(zz,'%03g') '.bmp']);
Inputimage=Inputimage(:,:,1);
temp=reshape(double(Inputimage)',irow*icol,1);
me=mean(temp);
st=std(temp);
Z=(temp-me)/st;
x_hat=Z*128+128;
a_hat=x_hat-m;
omega_h=[];
for i=1:M
   o=dot(a_hat,U_norm(:,i));
   omega_h=[omega_h; o];
end
e=[];
for i=1:size(omega,2)
   mag=norm(omega_h-omega(:,i));
   e=[e mag];
end
[temp idx]=min(e);
disp([num2str(zz), '번 얼굴입력은 ' num2str(idx), '번 얼굴데이터로 인식되었습니다']);
if idx==zz
   cnt=cnt+1; 
end

end
disp(['얼굴 인식률은 ' num2str(cnt/M*100), '%입니다']);
