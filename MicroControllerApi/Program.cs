using MicroControllerApi.Extension;
using Scalar.AspNetCore;

var builder = WebApplication.CreateBuilder(args);

builder.SetupEnvVariables();
builder.InitLogsWithSerilog();
builder.InitDbWithPostgres();
builder.AddHealthChecksForEndpointAndDb();

builder.Services.AddControllers();
// Learn more about configuring OpenAPI at https://aka.ms/aspnet/openapi
builder.Services.AddOpenApi();

var app = builder.Build();

app.MapLivenessHealthCheck();
app.MapReadinessHealthCheck();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.MapOpenApi();
    app.MapScalarApiReference();
}

app.UseHttpsRedirection();

app.UseAuthorization();

app.MapControllers();

app.Run();