namespace LabReportGenerator
{
    public interface IReportBuilder
    {
        void AddHeader(string title, string student, string group);
        void AddSections(string goal, string task, string theory);
        void AddDisciplineSpecific(string discipline, string experiment, string imagePath, string code);
        void AddFooter(string results, string analysis, string conclusion);
        Report GetResult();
    }
}