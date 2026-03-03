namespace LabReportGenerator
{
    public class ReportDirector_WithPattern
    {
        public Report Construct(IReportBuilder builder, ReportData data)
        {
            builder.AddHeader(data.Title, data.StudentName, data.Group);
            builder.AddSections(data.Goal, data.Task, data.Theory);
            builder.AddDisciplineSpecific(data.Discipline, data.Experiment, data.ImagePath, data.Code);
            builder.AddFooter(data.Results, data.Analysis, data.Conclusion);
            return builder.GetResult();
        }
    }
}