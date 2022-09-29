#include <bits/stdc++.h>
using namespace std;

class Course{
    private:
    string courseName;
    string lecturerName;
    int numberOfEnrolledStudents;
    public:
    Course(string courseName , string lecturerName) : courseName(courseName) , lecturerName(lecturerName){
        numberOfEnrolledStudents = 0;
        
    }
    string getCourseName(){
        return courseName;
    }
    string getLecturerName(){
        return lecturerName;
    }

    bool operator== (Course const &other){
        if(courseName == other.courseName && lecturerName == other.lecturerName
        && numberOfEnrolledStudents == other.numberOfEnrolledStudents){
            return true;
        }else{
            return false;
        }
    }
    bool operator>(Course const &other){
        if(courseName > other.courseName) return true;
        else return false;
    }
    bool operator<(Course const &other){
        if(courseName < other.courseName) return true;
        else return false;
    }

};
class User{
    protected:
    string userName;
    string password;
    string email;
    string fullName;
    vector<Course> courses; // the courses in which the student is enrolled
    public:
    User(string userName , string password,string email , string fullName){
        this->userName = userName;
        this->password = password;
        this->email = email;
        this->fullName = fullName;
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
    vector<Course> get_courses(){
        return courses;
    }
    bool isValidCourseIndex(int index){
        return index >= 1 && index <= courses.size();
    }
    Course getCourseByIndex(int index){
        return courses[index - 1];
    }
    void addCourse(Course &course){
        courses.push_back(course);
    }
    void deleteCourseByIndex(int index){
        courses.erase(courses.begin() + index - 1);
    }
    void deleteCourse(Course &course){
        for(int i = 0; i < courses.size(); i++){
            if(courses[i] == course){
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
};


class Student : public User{
    
    public:
    Student(string userName , string password,string email , string fullName) 
    : User(userName, password , email , fullName){
    
    }
    int getNumberOfEnrolledCourses(){
        return courses.size();
    }
    void viewCourses(){
        for(int i = 0; i < courses.size(); i++){
            cout << "\t\t\t" << i + 1 << "- " << courses[i].getCourseName() << " by "
            << courses[i].getLecturerName() << "\n";
        }
    }
    bool isEnrolled(Course _course){
        for(Course course : courses){
            if(_course == course) return true;
        }
        return false;
    }
    
    // it should be checked before if this index is correct
    // The index must be 1-based
    
    
    bool operator== (Student const &other){
        if(userName == other.userName && password == other.password 
        && email == other.email && fullName == other.fullName){
            return true;
        }else{
            return false;
        }
    }
    bool operator>(Student const &other){
        if(fullName > other.fullName) return true;
        else return false;
    }
    bool operator<(Student const &other){
        if(fullName < other.fullName) return true;
        else return false;
    }
};
class Lecturer : public User{
    
    public:
    Lecturer(string userName , string password,string email , string fullName) 
    : User(userName, password , email , fullName){
        
    }
    void viewCourses(){
        for(int i = 0; i < courses.size(); i++){
            cout << "\t\t\t" << i + 1 << "- " << courses[i].getCourseName() << "\n";
        }
    }
    
};
vector<Student> students; // list of all students
vector<Lecturer> lecturers; // list of all lecturers
vector<Course> courses; // list of all courses
vector<pair<Course, vector<Student>>> studentsInCourse; // list of students in specific course

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

bool isValidStudentIndex(Course &course , int index){
    for(int i = 0; i < studentsInCourse.size(); i++){
        if(studentsInCourse[i].first == course){
            return index >= 1 && index <= studentsInCourse[i].second.size();
        }
    }
    return false;
}
// we have to check first if the index is valid
Student getStudentInCourse(Course &course , int index){
    for(int i = 0; i < studentsInCourse.size(); i++){
        if(studentsInCourse[i].first == course){
            return studentsInCourse[i].second[index - 1];
        }
    }
    return students[0]; // this won't happen because we check first
}
// it should be checked first that the student is not enrolled in the course
void addCourse(Student &student, Course &course){
    student.addCourse(course);
    for(int i = 0; i < courses.size(); i++){
        if(studentsInCourse[i].first == course){
            studentsInCourse[i].second.push_back(student);
            break;
        }
    }
}

void addCourse(Lecturer &lecturer, Course &course){
    lecturer.addCourse(course);
    courses.push_back(course);
    studentsInCourse.push_back({course , vector<Student>()});
}
void deleteCourse(Student &student , Course &course){
    student.deleteCourse(course);
    for(int i = 0; i < courses.size(); i++){
        if(studentsInCourse[i].first == course){
            for(int j = 0; j < studentsInCourse[i].second.size(); j++){
                if(studentsInCourse[i].second[j] == student){
                    studentsInCourse[i].second.erase(studentsInCourse[i].second.begin() + j);
                    break;
                }
            }
            break;
        }
    }
}

void deleteCourse(Lecturer &lecturer , Course &course){
    lecturer.deleteCourse(course);
    for(int i = 0; i < studentsInCourse.size(); i++){
        if(studentsInCourse[i].first == course){
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
}
void viewMyCoursesScreen(Student &student){
    cout << "\t\t\t=====================================================================\n\n";
    cout << "\t\t\t\t" << "Here is your courses list: \n"; 
    student.viewCourses();
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
                    Course _course = student.getCourseByIndex(numberOfCourse);
                    deleteCourse(student , _course);
                    viewMyCoursesScreen(student);
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
        if(studentsInCourse[i].first == course){
            for(int j = 0; j < studentsInCourse[i].second.size(); j++){
                cout << "\t\t\t" << j + 1 << "- " << studentsInCourse[i].second[j].get_fullName() << "\t\t"
                << studentsInCourse[i].second[j].get_userName() << "\n";
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
            cout << "Enter the student index: ";
            int index;
            cin >> index;
            if(isValidStudentIndex(course , index)){
                Student _student  = getStudentInCourse(course , index);
                deleteCourse(_student , course);
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
    lecturer.viewCourses();
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
                Course _course = lecturer.getCourseByIndex(index);
                deleteCourse(lecturer , _course);
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
    
    cout << "\t\t\t" << "1- Enroll in course.\n";
    cout << "\t\t\t" << "2- Go back.\n";
    do{
        cout << "\t\t\t" << "Your Choice: ";
        char option;
        cin >> option;
        if(option == '1'){
            cout << "\t\t\t" << "Enter your course number: ";
            int courseNumber;
            cin >> courseNumber;
            if(isValidCourseIndex(courseNumber)){
                if(!student.isEnrolled(courses[courseNumber - 1])){
                    addCourse(student, courses[courseNumber - 1]);
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
    lecturer.viewCourses();
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
            cout << "\t\t\t" << "2- Go back";
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
    cout << "Enter your old Email: ";
    string email;
    cin >> email;
    if(user->get_email() == email){
        cout << "Enter your new Email: ";
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
        cout << "Confirm your new password: ";
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
        char option;
        cin >> option;
        if(option == '1'){
            changeUsernameScreen(user);
            return;
        }else if(option == '2'){
            changeEmailScreen(user);
            return;
        }else if(option == '3'){
            changePasswordScreen(user);
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
    Course course (name , lecturer.get_fullName());
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
        
        for(Student student : students){
            if(student.get_userName() == user && student.get_password() == password){
                DashboardScreen(student);
                check = false;
                break;
            }
        }
        
        if(!check) continue;
        for(Lecturer lecturer : lecturers){
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
        fstudents << students[i].get_userName() << endl;
        fstudents << students[i].get_password() << endl;
        fstudents << students[i].get_fullName() << endl;
        fstudents << students[i].get_email() << endl;
        vector<Course> c = students[i].get_courses();
        temp  = to_string(c.size());
        fstudents << temp << endl;
        for(int j = 0; j < c.size(); j++){
            fstudents << c[j].getCourseName() << endl;
            fstudents << c[j].getLecturerName() << endl;
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
        flecturers << lecturers[i].get_userName() << endl;
        flecturers << lecturers[i].get_password() << endl;
        flecturers << lecturers[i].get_fullName() << endl;
        flecturers << lecturers[i].get_email() << endl;
        vector<Course> c = lecturers[i].get_courses();
        temp  = to_string(c.size());
        flecturers << temp << endl;
        for(int j = 0; j < c.size(); j++){
            flecturers << c[j].getCourseName() << endl;
            flecturers << c[j].getLecturerName() << endl;
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
        Course t = studentsInCourse[i].first;
        sc << t.getCourseName() << endl;
        sc << t.getLecturerName() << endl;
        vector<Student> c = studentsInCourse[i].second;
        temp = to_string(c.size());
        sc << temp << endl;
        for(int j = 0; j < c.size(); j++){
            sc << c[j].get_userName() << endl;
            sc << c[j].get_password() << endl;
            sc << c[j].get_fullName() << endl;
            sc << c[j].get_email() << endl;
            vector<Course> v = c[j].get_courses();
            temp  = to_string(v.size());
            sc << temp << endl;
            for(int k = 0; k < v.size(); k++){
                sc << v[k].getCourseName() << endl;
                sc << v[k].getLecturerName() << endl;
            }
        }
    }
    sc.close();
    studentsInCourse.clear();


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
        string courseName , lecturerName;
        getline(fstudents , userName);
        getline(fstudents , password);
        getline(fstudents , fullName);
        getline(fstudents , email);
        getline(fstudents , temp);
        int numberCourses = stoi(temp);
        Student student(userName , password , email , fullName);
        for(int j = 0; j < numberCourses; j++){
            getline(fstudents , courseName);
            getline(fstudents , lecturerName);
            Course c(courseName , lecturerName);
            student.addCourse(c);
        }
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
        string courseName , lecturerName;
        getline(flecturers , userName);
        getline(flecturers , password);
        getline(flecturers , fullName);
        getline(flecturers , email);
        getline(flecturers , temp);
        int numberCourses = stoi(temp);
        Lecturer lecturer(userName , password , email , fullName);
        for(int j = 0; j < numberCourses; j++){
            getline(flecturers , courseName);
            getline(flecturers , lecturerName);
            Course c(courseName , lecturerName);
            lecturer.addCourse(c);
        }
        lecturers.push_back(lecturer);

    }
    flecturers.close();

    fstream fcourses;
    fcourses.open("courses.txt");
    getline(fcourses , temp);
    size = stoi(temp);
    for(int i = 0; i < size; i++){
        string courseName , lecturerName;
        getline(fcourses, courseName);
        getline(fcourses ,lecturerName);
        Course course(courseName, lecturerName);
        courses.push_back(course);
    }
    fcourses.close();

    fstream sc;
    sc.open("studentsincourse.txt");
    getline(sc , temp);
    size = stoi(temp);
    for(int i = 0; i < size; i++){
        string courseName, lecturerName;
        getline(sc,  courseName);
        getline(sc , lecturerName);
        Course course (courseName, lecturerName);
        string temp2 = "";
        getline(sc , temp2);
        int size2 = stoi(temp2);
        vector<Student> st;
        for(int j = 0; j < size2; j++){
            string userName , password , fullName , email;
            string courseName , lecturerName;
            getline(sc , userName);
            getline(sc , password);
            getline(sc , fullName);
            getline(sc , email);
            getline(sc , temp);
            int numberCourses = stoi(temp);
            Student student(userName , password , email , fullName);
            for(int j = 0; j < numberCourses; j++){
                getline(sc , courseName);
                getline(sc , lecturerName);
                Course c(courseName , lecturerName);
                student.addCourse(c);
            }
            st.push_back(student);
        }
        studentsInCourse.push_back({course , st});
    }
    sc.close();


}
int main(){
    preprocessing();
    welcomeScreen();
    return 0;
}

/*
    two problems until now
    1- student in studnetsInCourse vector are not the same as students in students vector
    2- to solve this issue we have to make a parameter that totally identify every object
    making an id is a good suggestion
*/