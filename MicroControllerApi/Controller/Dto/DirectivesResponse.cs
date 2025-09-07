namespace MicroControllerApi.Controller.Dto;

public class DirectivesResponse
{
    public required short MinTemp { get; init; }
    public required short MaxTemp { get; init; }
    public required int ReportInterval { get; init; }
    public required int TempCheckInterval { get; init; }
    public required int CooldownPeriod { get; init; }
}