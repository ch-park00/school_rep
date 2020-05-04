x1=[2.5 0.5 2.2 1.9 3.1 2.3 2.0 1.0 1.5 1.1]';
x2=[2.4 0.7 2.9 2.2 3.0 2.7 1.6 1.1 1.6 0.9']';
%%
figure(1),plot(x1,x2,'o');hold on;plot([-1 4],[0 0],'k:');plot([0 0],[-1 4],'k:');
title('Original data');xlim([-1 4]);ylim([-1 4]);axis square;
x1_p=x1-mean(x1);
x2_p=x2-mean(x2);
%%
figure(2),plot(x1_p,x2_p,'o');hold on;plot([-1 4],[0 0],'k:');plot([0 0],[-1 4],'k:');
title('data with the means subtracted');xlim([-1 4]);ylim([-1 4]);axis square;
X_p=[x1_p x2_p];
C=cov(X_p)
%E=eigenvector, D=diagonalized matrix
[E,D]=eig(C)
temp=E(:,1);
E(:,1)=E(:,2);
E(:,2)=temp;

e_max=E(:,1);
%%
figure(3),plot(X_p(:,1),X_p(:,2),'ro');hold on;
plot([-2 2],[0 0],'k:');plot([0 0],[-2 2],'k:');
plot(X_p(:,1),E(2,1)/E(1,1)*X_p(:,1),'r:');
plot(X_p(:,1),E(2,2)/E(1,2)*X_p(:,1),'r:');
title('Mean adjusted data with eigenvectors overlayed');
xlim([-2 2]);ylim([-2 2]);axis square
%%
Y_all=X_p*E;
figure(4);
plot(Y_all(:,1),Y_all(:,2),'b+');hold on;
plot([-2 2],[0 0],'k:');plot([0 0],[-2 2],'k:');
xlim([-2 2]);ylim([-2 2]);
title('Data transformed with 2 eigenvectors');axis square

%%
[E,Y_all_func,D]=pca([x1,x2]);
figure(5);
plot(Y_all(:,1),Y_all(:,2),'bo');hold on;
plot(Y_all_func(:,1),-Y_all_func(:,2),'r*');
plot([-2 2],[0 0],'k:');plot([0 0],[-2 2],'k:');
xlim([-2 2]);ylim([-2 2]);
title('Data transformed with 2 eigenvectors');axis square


%%
y_pca=X_p*e_max;
figure(6);
plot(y_pca,zeros(size(y_pca)),'b+');hold on;
plot([-2 2],[0 0],'k:');plot([0 0],[-2 2],'k:');
xlim([-2 2]);ylim([-2 2]);
title('Data transformed with 1 eigenvectors');axis square

%%
figure(7);
plot(Y_all_func(:,1),zeros(size(x1)),'r*');hold on;
plot(y_pca,zeros(size(y_pca)),'b+');
plot([-2 2],[0 0],'k:');plot([0 0],[-2 2],'k:');
xlim([-2 2]);ylim([-2 2]);
title('Data transformed with 1 eigenvectors');axis square

%% 데이터 원상복구
X_p_new=y_pca*e_max';

x1_mean=mean(x1)*ones(10,1);
x2_mean=mean(x2)*ones(10,1);

X_hat(:,1)=X_p_new(:,1)+x1_mean;
X_hat(:,2)=X_p_new(:,2)+x2_mean;

figure(8);
plot(X_hat(:,1),X_hat(:,2),'b+');hold on;
plot([-1 4],[0 0],'k:');plot([0 0],[-1 4],'k:');
xlim([-1 4]);ylim([-1 4]);axis square;
title('Original data restored using only a single eigenvector');