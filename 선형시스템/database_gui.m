function varargout = database_gui(varargin)
% DATABASE_GUI MATLAB code for database_gui.fig
%      DATABASE_GUI, by itself, creates a new DATABASE_GUI or raises the existing
%      singleton*.
%
%      H = DATABASE_GUI returns the handle to a new DATABASE_GUI or the handle to
%      the existing singleton*.
%
%      DATABASE_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DATABASE_GUI.M with the given input arguments.
%
%      DATABASE_GUI('Property','Value',...) creates a new DATABASE_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before database_gui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to database_gui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help database_gui

% Last Modified by GUIDE v2.5 03-Dec-2018 21:32:49

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @database_gui_OpeningFcn, ...
                   'gui_OutputFcn',  @database_gui_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before database_gui is made visible.
function database_gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to database_gui (see VARARGIN)
% Choose default command line output for database_gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);
set(handles.edit1,'string','현재 주소를 입력하세요');
set(handles.text2,'string',' ');
set(handles.text3,'string',' ');


% UIWAIT makes database_gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = database_gui_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.text2,'string','init ok');
set(handles.text3,'string','init ok');

load db_data.mat;
global new_data;
global new_data1;
%하나씩 매칭되는 거 있음.확인완료
for i=1:401
    for j=1:318
   if strcmp(data.response.body.items.item{i,1}.dutyName,...
           data2.response.body.items.item(j,1).dutyName)==1
       new_data{i,1}=data2.response.body.items.item(j,1);
   end
    end
    for j=1:401
   if strcmp(data.response.body.items.item{i,1}.hpid,...
           data1.response.body.items.item{j,1}.hpid)==1
       new_data1{i,1}=data1.response.body.items.item{j,1};
   end
    end
end
place=get(handles.edit1,'string');
api = 'https://maps.googleapis.com/maps/api/';
url = [api 'geocode/json?address=' place ...
        '&key=AIzaSyDpgBOWLjCw4sZI3I9q3xU8jPNttyUSkQ4'];
global answer;
answer= webread(url);
if ~strcmp(answer.status,'OK')
    set(handles.text2,'string','주소를 잘못 입력하셨습니다');
else
lat=answer.results.geometry.location.lat;
lng=answer.results.geometry.location.lng;

idx=0;
min=9999;
for i=1:401
    if ischar(new_data1{i,1}.wgs84Lat)==1
       temp(i,1)=str2double(new_data1{i,1}.wgs84Lat); 
    else
        temp(i,1)=new_data1{i,1}.wgs84Lat;
    end
    if ischar(new_data1{i,1}.wgs84Lon)==1
        temp1(i,1)=str2double(new_data1{i,1}.wgs84Lon);
    else
        temp1(i,1)=new_data1{i, 1}.wgs84Lon;
    end
    
end
idx=0;
min=999;
for i=1:401
    latdist=abs(lat-temp(i,1));
    lngdist=abs(lng-temp1(i,1));
    if min>latdist^2+lngdist^2
        min=latdist^2+lngdist^2;
        idx=i;
    end
end
set(handles.text2,'string',[new_data1{idx, 1}.dutyName sprintf('\n') new_data1{idx, 1}.dutyAddr]);
temp=find(~cellfun('isempty', new_data));
 for i=1:length(temp)
       if temp(i)==idx
           temp=99;
           break;
       end
 end
 if i==length(temp)
     temp=0;
 end
if temp==99
set(handles.text3,'string',['응급실 수용가능인원:' num2str(data.response.body.items.item{idx,1}.hvec) sprintf('\n')...
    '응급실 사용가능여부:' new_data{idx, 1}.MKioskTy25 sprintf('\n')...
    '응급실 전화번호:' new_data1{idx, 1}.dutyTel3 sprintf('\n')...
    '뇌출혈 수술가능여부:' new_data{idx, 1}.MKioskTy1 sprintf('\n')...
    '뇌경색의재관류:' new_data{idx, 1}.MKioskTy2 sprintf('\n')...
    '심근경색:' new_data{idx, 1}.MKioskTy3 sprintf('\n')....
    '복부손상수술:' new_data{idx, 1}.MKioskTy4 sprintf('\n')...
    '사지접합수술:' new_data{idx, 1}.MKioskTy5 sprintf('\n')...
    '응급내시경:' new_data{idx, 1}.MKioskTy6 sprintf('\n')...
    '응급투석:' new_data{idx, 1}.MKioskTy7 sprintf('\n')...
    '조산산모:' new_data{idx, 1}.MKioskTy8 sprintf('\n')...
    '정신질환자 수용여부:' new_data{idx, 1}.MKioskTy9 sprintf('\n')...
    '신생아:' new_data{idx, 1}.MKioskTy10 sprintf('\n')...
    '중증화상:' new_data{idx, 1}.MKioskTy11 sprintf('\n')]);
else
    set(handles.text3,'string','해당 병원에 대한 정보가 없습니다');
end
end