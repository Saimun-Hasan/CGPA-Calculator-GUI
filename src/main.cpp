#include <wx/wx.h>
#include <wx/tokenzr.h>

class CGPACalculator : public wxFrame
{
public:
    CGPACalculator(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300))
    {
        // Create UI elements
        wxPanel *panel = new wxPanel(this, wxID_ANY);
        wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

        // GPA Calculation button
        wxButton *gpaButton = new wxButton(panel, wxID_ANY, wxT("Calculate GPA"));
        gpaButton->SetBackgroundColour(wxColour(0, 128, 0));                                         // Set the background color
        gpaButton->SetForegroundColour(wxColour(255, 255, 255));                                     // Set the text color
        gpaButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD)); // Set the font
        gpaButton->SetSize(wxSize(200, 40));                                                         // Set the size

        vbox->Add(gpaButton, 0, wxALL | wxALIGN_CENTER, 5);

        // CGPA Calculation button
        wxButton *cgpaButton = new wxButton(panel, wxID_ANY, wxT("Calculate CGPA"));
        cgpaButton->SetBackgroundColour(wxColour(0, 0, 128));                                         // Set the background color
        cgpaButton->SetForegroundColour(wxColour(255, 255, 255));                                     // Set the text color
        cgpaButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD)); // Set the font
        cgpaButton->SetSize(wxSize(200, 40));                                                         // Set the size

        vbox->Add(cgpaButton, 0, wxALL | wxALIGN_CENTER, 5);

        // Method button
        wxButton *methodButton = new wxButton(panel, wxID_ANY, wxT("Method"));
        methodButton->SetBackgroundColour(wxColour(128, 0, 0));                                         // Set the background color
        methodButton->SetForegroundColour(wxColour(255, 255, 255));                                     // Set the text color
        methodButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD)); // Set the font
        methodButton->SetSize(wxSize(200, 40));                                                         // Set the size

        vbox->Add(methodButton, 0, wxALL | wxALIGN_CENTER, 5);

        // Exit button
        wxButton *exitButton = new wxButton(panel, wxID_ANY, wxT("Exit"));
        exitButton->SetBackgroundColour(wxColour(128, 128, 128));                                     // Set the background color
        exitButton->SetForegroundColour(wxColour(255, 255, 255));                                     // Set the text color
        exitButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD)); // Set the font
        exitButton->SetSize(wxSize(200, 40));                                                         // Set the size

        vbox->Add(exitButton, 0, wxALL | wxALIGN_CENTER, 5);

        // Bind button events to corresponding functions
        gpaButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CGPACalculator::OnCalculateGPA, this);
        cgpaButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CGPACalculator::OnCalculateCGPA, this);
        methodButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CGPACalculator::OnMethod, this);
        exitButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &CGPACalculator::OnExit, this);

        panel->SetSizer(vbox);
        Centre();
    }

private:
    wxStringTokenizer tokenizer;

    void OnCalculateGPA(wxCommandEvent &event)
    {
        int numSubjects;
        wxString input;

        // Get the number of subjects from the user
        input = wxGetTextFromUser(wxT("Enter the number of subjects:"), wxT("Subject Count"), wxT(""));

        // Check if the user clicked the cancel button
        if (input.IsEmpty())
            return; // Exit the function if the user clicked cancel

        // Convert the input to an integer
        long tempNumSubjects;
        input.ToLong(&tempNumSubjects);
        numSubjects = static_cast<int>(tempNumSubjects);

        float *credits = new float[numSubjects];
        float *points = new float[numSubjects];

        // Get credit and point values for each subject
        for (int i = 0; i < numSubjects; i++)
        {
            wxString creditInput, pointInput;

            // Get credit value for subject i
            creditInput = wxGetTextFromUser(wxString::Format(wxT("Enter the credit for subject %d:"), i + 1), wxT("Credit"), wxT(""));

            // Check if the user clicked the cancel button
            if (creditInput.IsEmpty())
            {
                delete[] credits;
                delete[] points;
                return; // Exit the function if the user clicked cancel
            }

            long tempCredit;
            creditInput.ToLong(&tempCredit);
            credits[i] = static_cast<float>(tempCredit);

            // Get point value for subject i
            pointInput = wxGetTextFromUser(wxString::Format(wxT("Enter the point of subject %d:"), i + 1), wxT("Point"), wxT(""));

            // Check if the user clicked the cancel button
            if (pointInput.IsEmpty())
            {
                delete[] credits;
                delete[] points;
                return; // Exit the function if the user clicked cancel
            }

            long tempPoint;
            pointInput.ToLong(&tempPoint);
            points[i] = static_cast<float>(tempPoint);
        }

        // Calculate GPA
        float totalCredits = 0.0;
        float totalPoints = 0.0;
        for (int i = 0; i < numSubjects; i++)
        {
            totalCredits += credits[i];
            totalPoints += credits[i] * points[i];
        }

        float gpa = totalPoints / totalCredits;

        // Display the GPA
        wxString message = wxString::Format(wxT("Total Points: %.2f\nTotal Credits: %.2f\nGPA: %.2f"), totalPoints, totalCredits, gpa);
        wxMessageBox(message, wxT("GPA Calculation"), wxOK | wxICON_INFORMATION);

        delete[] credits;
        delete[] points;
    }

    void OnCalculateCGPA(wxCommandEvent &event)
    {
        int numSemesters;
        wxString input;

        // Get the number of semesters from the user
        input = wxGetTextFromUser(wxT("Enter the number of semesters:"), wxT("Semester Count"), wxT(""));

        // Check if the user clicked Cancel
        if (input.IsEmpty())
        {
            wxMessageBox(wxT("Operation canceled."), wxT("Cancel"), wxOK | wxICON_INFORMATION);
            return;
        }

        // Convert the input to an integer
        long tempNumSemesters;
        input.ToLong(&tempNumSemesters);
        numSemesters = static_cast<int>(tempNumSemesters);

        float *semesterGPAs = new float[numSemesters];

        // Get GPA for each semester
        for (int i = 0; i < numSemesters; i++)
        {
            wxString gpaInput;

            // Get GPA for semester i
            gpaInput = wxGetTextFromUser(wxString::Format(wxT("Enter the GPA for semester %d:"), i + 1), wxT("GPA"), wxT(""));

            // Check if the user clicked Cancel
            if (gpaInput.IsEmpty())
            {
                wxMessageBox(wxT("Operation canceled."), wxT("Cancel"), wxOK | wxICON_INFORMATION);
                delete[] semesterGPAs; // Clean up allocated memory
                return;
            }

            double gpaValue;
            gpaInput.ToDouble(&gpaValue);
            semesterGPAs[i] = static_cast<float>(gpaValue);
        }

        // Calculate CGPA
        float totalGPA = 0.0;
        for (int i = 0; i < numSemesters; i++)
        {
            totalGPA += semesterGPAs[i];
        }

        float cgpa = totalGPA / numSemesters;

        // Display the CGPA
        wxString message = wxString::Format(wxT("Total GPA: %.2f\nNumber of Semesters: %d\nCGPA: %.2f"), totalGPA, numSemesters, cgpa);
        wxMessageBox(message);

        delete[] semesterGPAs;
    }

    void OnMethod(wxCommandEvent &event)
    {
        wxString methodDescription = wxT("Method of Calculating GPA & CGPA\n\n");
        methodDescription += wxT("GPA = Sum of (Credit * Point) / Total credits\n");
        methodDescription += wxT("CGPA = Sum of GPA / Number of semesters\n\n");
        methodDescription += wxT("This method calculates the Grade Point Average (GPA) by multiplying the credit hours of each subject by its corresponding point value and then dividing the sum of these values by the total credits.\n\n");
        methodDescription += wxT("The Cumulative Grade Point Average (CGPA) is calculated by summing up the GPAs for each semester and dividing the total GPA by the number of semesters.\n");

        wxMessageBox(methodDescription, wxT("Method Description"));
    }

    void OnExit(wxCommandEvent &event)
    {
        Close();
    }
};

class CGPACalculatorApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        CGPACalculator *calculator = new CGPACalculator(wxT("CGPA Calculator"));
        calculator->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(CGPACalculatorApp);
