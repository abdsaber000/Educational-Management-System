#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<regex>
using namespace std;

int idCounter  = 0;
int idCourseCounter = 0;
class Course{
    private:
    string courseName;
    string lecturerName;
    int courseId;
    int lecturerId;
    public:
    Course(string courseName , string lecturerName , int lectureId) : courseName(courseName) , lecturerName(lecturerName){
        idCourseCounter++;
        courseId = idCourseCounter;
        this->lecturerId = lecturerId;
        
    }
    string getCourseName(){
        return courseName;
    }
    string getLecturerName(){
        return lecturerName;
    }
    int getCourseId(){
        return courseId;
    }
    int getLecturerId(){
        return lecturerId;
    }
    void setId(int id){
        courseId = id;
    }
    bool operator== (Course const &other){
        if(courseId == other.courseId){
            return true;
        }else{
            return false;
        }
    }

};
class User{
    protected:
    string userName;
    string password;
    string email;
    string fullName;
    int id;
    vector<int> courses; // the courses in which the student is enrolled
    public:
    User(string userName , string password,string email , string fullName){
        this->userName = userName;
        this->password = password;
        this->email = email;
        this->fullName = fullName;
        idCounter++;
        id = idCounter;
    }
    ~User(){
        courses.clear();
    }
    string get_userName(){
        return userName;
    }
    string get_password(){
        return password;
    }
    string get_fullName(){
        return fullName;
    }
    string get_email(){
        return email;
    }
    int get_id(){
        return id;
    }
    vector<int> get_courses(){
        return courses;
    }
    bool isValidCourseIndex(int index){
        return index >= 1 && index <= courses.size();
    }
    int getCourseByIndex(int index){
        return courses[index - 1]; // return the id of the course
    }
    void addCourse(int id){
        courses.push_back(id);
    }
    void deleteCourseByIndex(int index){
        courses.erase(courses.begin() + index - 1);
    }
    void deleteCourse(int id){
        for(int i = 0; i < courses.size(); i++){
            if(courses[i] == id){
                courses.erase(courses.begin() + i);
                break;
            }
        }
    }
    void setUsername(string username){
        this->userName = username;
    }
    void setEmail(string email){
        this->email = email;
    }
    void setPassword(string password){
        this->password = password;
    }
    // use this function only when you are reading 
    void setId(int id){
        this->id = id;
    }
};


class Student : public User{
    
    public:
    Student(string userName , string password,string email , string fullName) 
    : User(userName, password , email , fullName){
    
    }
    int getNumberOfEnrolledCourses(){
        return courses.size();
    }
    void viewCourses(vector<Course> &other){
        for(int i = 0; i < courses.size(); i++){
            for(int j = 0; j < other.size(); j++){
                if(other[j].getCourseId() == courses[i]){
                    cout << "\t\t\t" << i + 1 << "- " << other[j].getCourseName() << " by "
                    << other[j].getLecturerName() << "\n";
                }
            }
        }
    }
    bool isEnrolled(int id){
        for(int courseId : courses){
            if(courseId == id) return true;
        }
        return false;
    }
    
    // it should be checked before if this index is correct
    // The index must be 1-based
    
    
    bool operator== (Student const &other){
        if(id == other.id){
            return true;
        }else return false;
    }
};
class Lecturer : public User{
    
    public:
    Lecturer(string userName , string password,string email , string fullName) 
    : User(userName, password , email , fullName){
        
    }
    void viewCourses(vector<Course> &other){
        for(int i = 0; i < courses.size(); i++){
            for(int j = 0; j < other.size(); j++){
                if(other[j].getCourseId() == courses[i]){
                    cout << "\t\t\t" << i + 1 << "- " << other[j].getCourseName() << "\n";
                }
            }
        }
    }
    
};
vector<Student> students; // list of all students
vector<Lecturer> lecturers; // list of all lecturers
vector<Course> courses; // list of all courses
vector<pair<int, vector<int>>> studentsInCourse; // list of students in specific course

// check if there a user has this username
bool isValidStudent(string username){
    for(Student student : students){
        if(student.get_userName() == username) return true;
    }
    return false;
}
// the function is valid should be used before 
Student getValidStudent(string username){
    for(Student student : students){
        if(student.get_userName() == username) return student;
    }
    return students[0]; // this scenario won't happen because we check if it exists in advance

}
bool isValidLecturer(string username){
    for(Lecturer lecturer : lecturers){
        if(lecturer.get_userName() == username) return true;
    }
    return false;
}

Lecturer getValidLecturer(string username){
    for(Lecturer lecturer : lecturers){
        if(lecturer.get_userName() == username) return lecturer;
    }
    return lecturers[0]; // this scenario won't happen because we check if it exists in advance
}

bool isValidUser(string username){
    return isValidStudent(username) || isValidLecturer(username);
}

int isValidPassword(string password){
    const regex pattern("\\w+");
    return (password.size() >= 8) && regex_match(password, pattern);
}

bool isValidNumber(string number){
    if(number.size() > 9) return false;
    const regex pattern("^[0-9]*$");
    return regex_match(number , pattern);
}
bool isValidEmail(string email){
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email , pattern);
}

bool isEmailExist(string email){
    for(Student student : students){
        if(student.get_email() == email) return true;
    }
    for(Lecturer lecturer : lecturers){
        if(lecturer.get_email() == email) return true;
    }
    return false;
}

bool isValidCourseIndex(int index){
    return index >= 1 && index <= courses.size();
}

bool isValidStudentIndex(int courseId , int index){
    for(int i = 0; i < studentsInCourse.size(); i++){
        if(studentsInCourse[i].first == courseId){
            return index >= 1 && index <= studentsInCourse[i].second.size();
        }
    }
    return false;
}
// we have to check first if the index is valid
//this function will return the id of the student
int getStudentInCourse(int courseId , int index){
    for(int i = 0; i < studentsInCourse.size(); i++){
        if(studentsInCourse[i].first == courseId){
            return studentsInCourse[i].second[index - 1];
        }
    }
    return students[0].get_id(); // this won't happen because we check first
}
// it should be checked first that the student is not enrolled in the course
void addCourse(Student &student, Course &course){
    int studentId = student.get_id();
    int courseId = course.getCourseId();
    student.addCourse(courseId);
    for(int i = 0; i < studentsInCourse.size(); i++){
        if(studentsInCourse[i].first == courseId){
            studentsInCourse[i].second.push_back(student.get_id());
            break;
        }
    }
}

void addCourse(Lecturer &lecturer, Course &course){
    lecturer.addCourse(course.getCourseId());
    courses.push_back(course);
    studentsInCourse.push_back({course.getCourseId() , vector<int>()});
}
void deleteCourse(Student &student, Course course){
    int courseId = course.getCourseId();
    student.deleteCourse(courseId);
    for(int i = 0; i < studentsInCourse.size(); i++){
        if(studentsInCourse[i].first == courseId){
            for(int j = 0; j < studentsInCourse[i].second.size(); j++){
                if(studentsInCourse[i].second[j] == student.get_id()){
                    studentsInCourse[i].second.erase(studentsInCourse[i].second.begin() + j);
                    break;
                }
            }
            break;
        }
    }
}

void deleteCourse(Lecturer &lecturer , Course course){
    lecturer.deleteCourse(course.getCourseId());
    for(int i = 0; i < studentsInCourse.size(); i++){
        if(studentsInCourse[i].first == course.getCourseId()){
            studentsInCourse.erase(studentsInCourse.begin() + i);
            break;
        }
    }
    for(int i = 0; i < courses.size(); i++){
        if(courses[i] == course){
            courses.erase(courses.begin() + i);
            break;
        }
    }
    for(int i = 0; i < students.size(); i++){
        students[i].deleteCourse(course.getCourseId());
    }
}
void viewMyCoursesScreen(Student &student){
    cout << "\t\t\t=====================================================================\n\n";
    cout << "\t\t\t\t" << "Here is your courses list: \n"; 
    student.viewCourses(courses);
    cout << "\n\n";
    cout << "\t\t\t" << "1- Delete a course.\n";
    cout << "\t\t\t" << "2- Go back.\n";
    do{
        cout << "\t\t\t" << "Your choice: ";
        char option;
        cin >> option;
        if(option == '1'){
            do{
                cout << "\t\t\tEnter your course number: ";
                int numberOfCourse;
                cin >> numberOfCourse;
                if(student.isValidCourseIndex(numberOfCourse)){
                    int courseId = student.getCourseByIndex(numberOfCourse);
                    for(int i = 0; i < courses.size(); i++){
                        if(courses[i].getCourseId() == courseId){

                            deleteCourse(student , courses[i]);
                        }
                    } 
                    viewMyCoursesScreen(student);
                    return;
                }else{
                    cout << "\t\t\tSorry, the course index is incorrect.\n";
                    return;
                }

            }while(true);
        }else if(option == '2'){
            return;
        }
    }while(true);
    return;

}

void printStudentsInCourse(Course &course){
    cout << "\t\t\t" << "Student Name\t\tusername\n";
    for(int i = 0; i < studentsInCourse.size(); i++){
        if(studentsInCourse[i].first == course.getCourseId()){
            for(int j = 0; j < studentsInCourse[i].second.size(); j++){
                for(int k = 0; k < students.size(); k++){
                    if(students[k].get_id() == studentsInCourse[i].second[j]){
                        cout << "\t\t\t" << j + 1 << "- " << students[k].get_fullName() << "\t\t"
                        << students[k].get_userName() << "\n";
                        break;
                    }
                }
            }

            break;
        }
    }
}

void viewStudentsInCourseScreen(Course &course){
    cout << "\t\t\t=====================================================================\n\n";
    printStudentsInCourse(course);
    cout << "\n\n";
    cout << "\t\t\t" << "1- remove a student from the course.\n";
    cout << "\t\t\t" << "2- Go back.\n";
    do{
        cout << "\t\t\t" << "Your choice: ";
        char option;
        cin >> option;
        if(option == '1'){
            cout << "\t\t\tEnter the student index: ";
            int index;
            cin >> index;
            if(isValidStudentIndex(course.getCourseId() , index)){
                int studentId  = getStudentInCourse(course.getCourseId() , index);
                for(int i = 0; i < students.size(); i++){
                    if(students[i].get_id() == studentId){
                        deleteCourse(students[i] , course);
                    }
                }
                cout << "\t\t\t" << "The student was removed successfully.\n";
            }else{
                cout << "\t\t\t" << "Sorry, The index is incorrect.\n";
            }
            return;
        }else if(option == '2'){
            return;
        }
    }while(true);
}
// overloading
void viewMyCoursesScreen(Lecturer &lecturer){
    cout << "\t\t\t=====================================================================\n\n";
    cout << "\t\t\t\t" << "Here is your courses list: \n"; 
    lecturer.viewCourses(courses);
    cout << "\n";
    cout << "\t\t\t" << "1- View students in certain course.\n";
    cout << "\t\t\t" << "2- Remove a course.\n";
    cout << "\t\t\t" << "3- Go back.\n";
    do{
        cout << "\t\t\t" << "Make your choice: ";
        char option ;
        cin >> option;
        if(option == '1'){
            cout << "\t\t\t" << "Enter the index of the course: ";
            int number;
            cin >> number;
            if(isValidCourseIndex(number)){
                viewStudentsInCourseScreen(courses[number - 1]);
                viewMyCoursesScreen(lecturer);
                return;
            }else{
                cout << "\t\t\t" << "Sorry, the course index is not correct!\n";
            }
        }else if(option == '2'){
            cout << "\t\t\t" << "Enter the index of the course: ";
            int index;
            cin >> index;
            if(isValidCourseIndex(index)){
                int courseId = lecturer.getCourseByIndex(index);
                for(int i = 0; i < courses.size(); i++){
                    if(courses[i].getCourseId() == courseId){

                        deleteCourse(lecturer , courses[i]);
                        viewMyCoursesScreen(lecturer);
                        return;
                    }

                }
            }else{
                cout << "\t\t\t" << "Sorry, the course index is not correct!\n";
            }
        }else if(option == '3'){
            return;
        }
    }while(true);
    return;

}
// views all available courses in general
void viewCoursesScreen(Student &student){
    cout << "\t\t\t=====================================================================\n\n";
    cout << "\t\t\t\t" << "Here is all available courses: \n"; 

    for(int i = 0; i < courses.size(); i++){
        cout << "\t\t\t" << i + 1 << "- " << courses[i].getCourseName() << " by "
            << courses[i].getLecturerName() << "\n";
    }
    
    do{
        cout << "\t\t\t" << "1- Enroll in course.\n";
        cout << "\t\t\t" << "2- Go back.\n";
        cout << "\t\t\t" << "Your Choice: ";
        char option;
        cin >> option;
        if(option == '1'){
            cout << "\t\t\t" << "Enter your course number: ";
            int courseNumber;
            cin >> courseNumber;
            if(isValidCourseIndex(courseNumber)){
                if(!student.isEnrolled(courses[courseNumber - 1].getCourseId())){
                    addCourse(student, courses[courseNumber - 1]);
                    return;
                }
                else{
                    cout << "\t\t\t" << "Sorry you are enrolled in the course.\n";
                }
            }else{
                cout << "\t\t\t" << "Sorry the course number is not valid.\n";
            }

        }else if(option == '2'){
            return;
        }
    }while(true);

}

//TODO
void viewCoursesScreen(Lecturer &lecturer){
    cout << "\t\t\t=====================================================================\n\n";
    lecturer.viewCourses(courses);
    cout << "\n";
    
    cout << "\t\t\t" << "Press any key to go back.\n";
    char option;
    cin >> option;
    
}

void changeUsernameScreen(User * user){
    cout << "\t\t\t=====================================================================\n\n";
    do{
        cout << "\t\t\t" << "Enter your new username: ";
        string username;
        cin >> username;
        if(isValidUser(username)){
            cout << "\t\t\t" << "Sorry, this user name is used.\n";
            cout << "\t\t\t" << "1- Try again.\n";
            cout << "\t\t\t" << "2- Go back\n";
            do{
                cout << "\t\t\t" << "Make your choice : ";
                char option;
                cin >> option;
                if(option == '1'){
                    changeUsernameScreen(user);
                    return;
                }else if(option == '2'){
                    return;
                }
            }while(true);
            return;
        }else{
            user->setUsername(username);
            return;
        }
    }while(true);
}

void changeEmailScreen(User * user){
    cout << "\t\t\t=====================================================================\n\n";
    cout << "\t\t\tEnter your old Email: ";
    string email;
    cin >> email;
    if(user->get_email() == email){
        cout << "\t\t\tEnter your new Email: ";
        string newEmail;
        cin >> newEmail;
        if(isEmailExist(newEmail)){
            cout << "\t\t\t" << "Sorry, this email is used.\n";
        }else if(!isValidEmail(newEmail)){
            cout << "\t\t\t" << "Sorry, the email format is not valid.\n";
        }else{
            user->setEmail(newEmail);
            return;
        }
        cout << "\t\t\t" << "1- Try again.\n";
        cout << "\t\t\t" << "2- Go back.\n";
        do{
            cout << "\t\t\t" << "Make your choice: ";
            char option;
            cin >> option;
            if(option == '1'){
                changeEmailScreen(user);
                return;
            }else if(option == '2'){
                return;
            }
        }while(true);
    }
}
void changePasswordScreen(User * user){
    cout << "\t\t\t=====================================================================\n\n";
    cout << "\t\t\t" << "Enter your old password: ";
    string password;
    cin >> password;
    if(user->get_password() != password){
        cout << "\t\t\t" << "Your old password is incorrect.\n";
    }else{
        cout << "\t\t\t" << "Enter your new password: ";
        string newPassword;
        cin >> newPassword;
        cout << "\t\t\tConfirm your new password: ";
        string _newPassword;
        cin >> _newPassword;
        if(newPassword != _newPassword){
            cout << "\t\t\t" << "Sorry, your new password and confirm password are not the same.\n";
        }else if(!isValidPassword(newPassword)){
            cout << "\t\t\t" << "Sorry, your password is not valid.\n";
        }else{
            user->setPassword(newPassword);
            return;
        }
    }
        cout << "\t\t\t" << "1- Try again.\n";
        cout << "\t\t\t" << "2- Go back.\n";
        do{
            cout << "\t\t\t" << "Make your choice: ";
            char option;
            cin >> option;
            if(option == '1'){
                changePasswordScreen(user);
                return;
            }else if(option == '2'){
                return;
            }
        }while(true);
}
//TODO
void settingsScreen(User * user){
    cout << "\t\t\t=====================================================================\n\n";
    cout << "\t\t\t" << "1- Change your username.\n";
    cout << "\t\t\t" << "2- Change your email.\n";
    cout << "\t\t\t" << "3- Change your password.\n";
    cout << "\t\t\t" << "4- Go back.\n";
    do{
        cout << "\t\t\t" << "Make your choice: ";
        char option;
        cin >> option;
        if(option == '1'){
            changeUsernameScreen(user);
            settingsScreen(user);
            return;
        }else if(option == '2'){
            changeEmailScreen(user);
            settingsScreen(user);
            return;
        }else if(option == '3'){
            changePasswordScreen(user);
            settingsScreen(user);
            return;
        }else if(option == '4'){
            return;
        }
    }while(true);
}
// DONE
void DashboardScreen(Student &student){
    cout << "\t\t\t=====================================================================\n\n";
    cout << "\t\t\t\t" << "Welcome " << student.get_fullName() << "!\n";
    cout << "\t\t\t" << "Please make a choice: \n";
    cout << "\t\t\t\t" << "1- View my courses.\n"; // DONE
    cout << "\t\t\t\t" << "2- Explore available courses.\n"; // DONE
    cout << "\t\t\t\t" << "3- Settings.\n"; // DONE
    cout << "\t\t\t\t" << "4- Logout.\n"; // DONE
    do{
        cout << "\t\t\tYour choice: ";
        char option;
        cin >> option;
        cout << "\n";
        bool check = false;
        if(option == '1'){ 
            viewMyCoursesScreen(student);
            check = true;
        }else if(option == '2'){
            viewCoursesScreen(student);
            check = true;
        }else if(option == '3'){
            User * user = &student;
            settingsScreen(user);
            check = true;
        }else if(option == '4'){
            return;
        }
        if(check){
            DashboardScreen(student);
            return;
        }
    }while(true);

}
void CreateCourseScreen(Lecturer &lecturer){
    cout << "\t\t\t=====================================================================\n\n";
    cout << "\t\t\t" << "Enter the course name: ";
    string name;
    cin >> name;
    Course course (name , lecturer.get_fullName(), lecturer.get_id());
    addCourse(lecturer , course);
}
//TODO
void DashboardScreen(Lecturer &lecturer){
    cout << "\t\t\t=====================================================================\n\n";
    cout << "\t\t\t\t" << "Welcome " << lecturer.get_fullName() << "!\n";
    cout << "\t\t\t" << "Please make a choice: \n";
    cout << "\t\t\t\t" << "1- View my courses.\n"; // DONE
    cout << "\t\t\t\t" << "2- Explore available courses.\n"; // DONE
    cout << "\t\t\t\t" << "3- Create new course.\n"; // TODO
    cout << "\t\t\t\t" << "4- Settings.\n"; // DONE
    cout << "\t\t\t\t" << "5- Logout.\n"; // DONE
    do{
        cout << "\t\t\tYour choice: ";
        char option;
        cin >> option;
        cout << "\n";
        bool check = false;
        if(option == '1'){ 
            viewMyCoursesScreen(lecturer);
            check = true;
        }else if(option == '2'){
            viewCoursesScreen(lecturer);
            check = true;
        }else if(option == '3'){
            CreateCourseScreen(lecturer);
            check = true;
        }else if(option == '4'){
            User * user = &lecturer;
            settingsScreen(user);
            check = true;
        }else if(option == '5'){
            return;
        }
        if(check){
            DashboardScreen(lecturer);
            return;
        }
    }while(true);

}
void loginScreen(){
    cout << "\t\t\t=====================================================================\n\n";
    string user , password;
    bool check = true;
    do{
        cout << "\t\t\tUser Name: ";
        cin >> user;
        cout << "\n";
        cout << "\t\t\tPassword: ";
        cin >> password;
        cout << "\n";
        
        for(Student &student : students){
            if(student.get_userName() == user && student.get_password() == password){
                DashboardScreen(student);
                check = false;
                break;
            }
        }
        
        if(!check) continue;
        for(Lecturer &lecturer : lecturers){
            if(lecturer.get_userName() == user && lecturer.get_password() == password){
                DashboardScreen(lecturer);
                check = false;
                break;
            }
        }
        if(check){
            cout << "\t\t\t" << "Sorry your username or password is incorrect.\n\n";
            cout << "\t\t\t\t" << "1- Try again\n";
            cout << "\t\t\t\t" << "2- Back to welcome screen\n";
            do{
                cout << "\t\t\tYour choice: ";
                char option;
                cin >> option;
                cout << "\n";
                if(option == '1'){ 
                    break;
                }else if(option == '2'){
                    return;
                }
            }while(true);
        }

    }while(check);
}
bool SignUpScreen(int role){
    cout << "\t\t\t=====================================================================\n\n";
    string username , password, confirmPassword , fullName, email;
    do{
        cout << "\t\t\t\t" << "username: ";
        cin >> username;
        cout << "\n";
        cout << "\t\t\t\t" << "password: ";
        cin >> password;
        cout << "\n";
        cout << "\t\t\t\t" << "confirm password: ";
        cin >> confirmPassword;
        cout << "\n";
        cout << "\t\t\t\t" << "fullName: ";
        cin >> fullName;
        cout << "\n";
        cout << "\t\t\t\t" << "email: ";
        cin >> email;
        cout << "\n\n";

        // checking the validation of Data
        bool check = true;
        if(isValidUser(username)){
            check = false;
            cout  << "\t\t\t\tSorry your username exists already.\n";
        }
        else if(password != confirmPassword){
            check = false;
            cout << "\t\t\t\tThe password and the cofirm password are not the same.\n";
        }else if(!isValidPassword(password)){
            check = false;
            cout << "\t\t\t\tYour password is less than 8 characters or contians special characters like @#$.\n";
        }else if(!isValidEmail(email)){
            check = false;
            cout << "\t\t\t\tYour email is not valid.\n";
        }
        if(check){
            if(role == 1){
                Student student(username, password, email, fullName);
                students.push_back(student);
            }else{
                Lecturer lecturer(username, password, email, fullName);
                lecturers.push_back(lecturer);
            }
            return true; // this mean that the user signed up successfully
        }
        cout << "\t\t\t\t" << "1- Try again.\n";
        cout << "\t\t\t\t" << "2- Go back.\n";

        do{
            cout << "\t\t\t\tYour choice: ";
            char option;
            cin >> option;
            cout << "\n";
            if(option == '1'){ 
                break;
            }else if(option == '2'){
                return 0;
            }
        }while(true);

    }while(true);
    return 0;
}

void signUpScreen(){
    cout << "\t\t\t=====================================================================\n\n";
    
    cout << "\t\t\t" << "What is your role?\n";
    cout << "\t\t\t\t" << "1- Student.\n";
    cout << "\t\t\t\t" << "2- Lecturer.\n";
    cout << "\t\t\t\t" << "3- Back to welcome screen.\n";
    do{
        cout << "\t\t\tYour choice: ";
        char option;
        cin >> option;
        cout << "\n";
        if(option == '1'){ 
            if(SignUpScreen(1)){
                return;
            }else{
                signUpScreen();
                return;
            }
        }else if(option == '2'){
            if(SignUpScreen(2)){
                return;
            }else{
                signUpScreen();
                return;
            }
        }else if(option == '3'){
            return;
        }
    }while(true);

}
//It will be implemented at the end
void Exit(){
    //saving students
    fstream fstudents;
    fstudents.open("students.txt");
    string temp = "";
    temp = to_string(students.size());
    fstudents << temp << endl;
    for(int i = 0; i < students.size(); i++){
        fstudents << students[i].get_id() << endl;
        fstudents << students[i].get_userName() << endl;
        fstudents << students[i].get_password() << endl;
        fstudents << students[i].get_fullName() << endl;
        fstudents << students[i].get_email() << endl;
        vector<int> c = students[i].get_courses();
        temp  = to_string(c.size());
        fstudents << temp << endl;
        for(int j = 0; j < c.size(); j++){
            fstudents << c[j] << endl;
        }
    }
    fstudents.close();
    students.clear();
    //saving courses
    fstream fcourses;
    fcourses.open("courses.txt");
    temp = to_string(courses.size());
    fcourses << temp << endl;
    for(int i = 0; i < courses.size(); i++){
        fcourses << courses[i].getCourseId() << endl;
        fcourses << courses[i].getLecturerId() << endl;
        fcourses << courses[i].getCourseName() << endl;
        fcourses << courses[i].getLecturerName() << endl;
    }
    fcourses.close();
    courses.clear();

    // saving lecturers

    fstream flecturers;
    flecturers.open("lecturers.txt");
    temp = "";
    temp = to_string(lecturers.size());
    flecturers << temp << endl;
    for(int i = 0; i < lecturers.size(); i++){
        flecturers << lecturers[i].get_id() << endl;
        flecturers << lecturers[i].get_userName() << endl;
        flecturers << lecturers[i].get_password() << endl;
        flecturers << lecturers[i].get_fullName() << endl;
        flecturers << lecturers[i].get_email() << endl;
        vector<int> c = lecturers[i].get_courses();
        temp  = to_string(c.size());
        flecturers << temp << endl;
        for(int j = 0; j < c.size(); j++){
            flecturers << c[j] << endl;
        }
    }
    flecturers.close();
    lecturers.clear();

    // saving studentsInCourse
    fstream sc;
    sc.open("studentsincourse.txt");
    temp = to_string(studentsInCourse.size());
    sc << temp << endl;

    for(int i = 0; i < studentsInCourse.size(); i++){
        sc << studentsInCourse[i].first << endl;
        temp = to_string(studentsInCourse[i].second.size());
        sc << temp << endl;
        for(int j = 0; j < studentsInCourse[i].second.size(); j++){
            sc << studentsInCourse[i].second[j] << endl;
        }
    }
    sc.close();
    studentsInCourse.clear();

    fstream counters;
    counters.open("counters.txt");

    temp = to_string(idCounter);
    counters << temp << endl;
    temp = to_string(idCourseCounter);
    counters << temp << endl;

    counters.close();

}
void welcomeScreen(){
    cout << "\t\t\t=====================================================================\n";
    cout << "\t\t\t=====================================================================\n";
    cout << "\t\t\t=================== Educational Management System ===================\n";
    cout << "\t\t\t=====================================================================\n";
    cout << "\t\t\t=====================================================================\n";
    cout <<"\n\n\n\n";
    cout << "\t\t\t\t" << "Welcome to the Educational Management System!\n\n\n";
    cout << "\t\t\t" << "Please make a Choice:\n";
    cout << "\t\t\t\t" << "1- login\n";
    cout << "\t\t\t\t" << "2- sign up\n";
    cout << "\t\t\t\t" << "3- shutdown\n";
    char option;
    do{
        cout << "\t\t\t" << "Your Choice: ";
        cin >> option;
        cout << "\n";
        if(option == '1'){
            loginScreen();
            welcomeScreen();
            return;
        }else if(option == '2'){
            signUpScreen();
            welcomeScreen();
            return;
        }else if(option == '3'){
            Exit();
            return;
        }else{
            cout << "\t\t\t" << "Enter 1 ,2 or 3!\n";
        }
    }while(true);

}
// It will be implemented at the end
void preprocessing(){
    // students
    //saving students
    fstream fstudents;
    fstudents.open("students.txt");
    string temp = "";
    getline(fstudents , temp);
    int size = stoi(temp);
    for(int i = 0; i < size; i++){
        string userName , password , fullName , email;
        
        string id;
        getline(fstudents , id);

        getline(fstudents , userName);
        getline(fstudents , password);
        getline(fstudents , fullName);
        getline(fstudents , email);
        getline(fstudents , temp);
        int numberCourses = stoi(temp);
        Student student(userName , password , email , fullName);
        for(int j = 0; j < numberCourses; j++){
            string courseId;
            getline(fstudents , courseId);
            student.addCourse(stoi(courseId));
        }
        student.setId(stoi(id));
        students.push_back(student);

    }
    fstudents.close();

    fstream flecturers;
    flecturers.open("lecturers.txt");
    temp = "";
    getline(flecturers , temp);
    size = stoi(temp);
    for(int i = 0; i < size; i++){
        string userName , password , fullName , email;
        
        string id;
        getline(flecturers , id);

        getline(flecturers , userName);
        getline(flecturers , password);
        getline(flecturers , fullName);
        getline(flecturers , email);
        getline(flecturers , temp);
        int numberCourses = stoi(temp);
        Lecturer lecturer(userName , password , email , fullName);
        for(int j = 0; j < numberCourses; j++){
            string courseId;
            getline(flecturers , courseId);
            lecturer.addCourse(stoi(courseId));
        }
        lecturer.setId(stoi(id));
        lecturers.push_back(lecturer);

    }
    flecturers.close();

    fstream fcourses;
    fcourses.open("courses.txt");
    getline(fcourses , temp);
    size = stoi(temp);
    for(int i = 0; i < size; i++){
        string courseName , lecturerName , courseId , lecturerId;
        getline(fcourses , courseId);
        getline(fcourses , lecturerId);
        getline(fcourses, courseName);
        getline(fcourses ,lecturerName);
        Course course(courseName, lecturerName , stoi(lecturerId));
        course.setId(stoi(courseId));
        courses.push_back(course);
    }
    fcourses.close();

    fstream sc;
    sc.open("studentsincourse.txt");
    getline(sc , temp);
    size = stoi(temp);
    for(int i = 0; i < size; i++){
        string course;
        getline(sc , course);
        vector<int> v;
        getline(sc , temp);
        int size2 = stoi(temp);
        for(int j = 0; j < size2; j++){
            getline(sc , temp);
            v.push_back(stoi(temp));
        }
        studentsInCourse.push_back({stoi(course) , v});
    }
    sc.close();

    fstream counters;
    counters.open("counters.txt");
    getline(counters , temp);
    idCounter = stoi(temp);
    getline(counters , temp);
    idCourseCounter = stoi(temp);
    counters.close();
}
int main(){
    preprocessing();
    welcomeScreen();
    return 0;
}

