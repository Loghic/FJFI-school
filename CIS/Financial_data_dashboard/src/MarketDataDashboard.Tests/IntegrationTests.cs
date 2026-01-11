/*
using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using MarketDataDashboard.Data;
using MarketDataDashboard.Models;

namespace MarketDataDashboard.Tests;

public class IntegrationTests : IClassFixture<WebApplicationFactory<Program>>
{
    private readonly WebApplicationFactory<Program> _factory;

    public IntegrationTests(WebApplicationFactory<Program> factory)
    {
        _factory = factory.WithWebHostBuilder(builder =>
        {
            builder.ConfigureServices(services =>
            {
                // Replace real database with in-memory for tests
                var descriptor = services.SingleOrDefault(
                    d => d.ServiceType == typeof(DbContextOptions<StockContext>));

                if (descriptor != null)
                    services.Remove(descriptor);

                services.AddDbContext<StockContext>(options =>
                    options.UseInMemoryDatabase("TestDb"));
            });
        });
    }

    [Fact]
    public async Task HomePage_ReturnsSuccessStatusCode()
    {
        var client = _factory.CreateClient();

        var response = await client.GetAsync("/");

        response.EnsureSuccessStatusCode();
        Assert.Equal("text/html; charset=utf-8", response.Content.Headers.ContentType?.ToString());
    }

    [Fact]
    public async Task IndicatorsPage_ReturnsSuccessStatusCode()
    {
        var client = _factory.CreateClient();

        var response = await client.GetAsync("/Indicators");

        response.EnsureSuccessStatusCode();
    }

    [Fact]
    public async Task DownloadCsv_ReturnsValidCsv()
    {
        // Arrange - seed data
        using var scope = _factory.Services.CreateScope();
        var context = scope.ServiceProvider.GetRequiredService<StockContext>();

        var stock = new Stock { Symbol = "AAPL", Name = "Apple" };
        context.Stocks.Add(stock);
        context.PricePoints.Add(new PricePoint
        {
            Date = DateTime.Today,
            Open = 100, High = 105, Low = 99, Close = 103, Volume = 1000,
            StockId = stock.Id,
            Stock = stock
        });
        await context.SaveChangesAsync();

        var client = _factory.CreateClient();

        // Act
        var response = await client.GetAsync("/Index?handler=Download&symbol=AAPL");

        // Assert
        response.EnsureSuccessStatusCode();
        Assert.Equal("text/csv", response.Content.Headers.ContentType?.MediaType);

        var content = await response.Content.ReadAsStringAsync();
        Assert.Contains("Date,Open,High,Low,Close,Volume", content);
    }

    [Fact]
    public async Task PredictionResult_BeforeStart_ReturnsNull()
    {
        var client = _factory.CreateClient();

        var response = await client.GetAsync("/?handler=PredictionResult&symbol=AAPL");

        response.EnsureSuccessStatusCode();
        var content = await response.Content.ReadAsStringAsync();
        Assert.Equal("null", content);
    }
}
*/
