#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include <vector>
#include <map>
#include <string>
#include <numeric>
#include <algorithm>
#include <memory>

namespace simframework {

    enum class Aggregation {
        Mean,
        Median,
        Min,
        Max
    };

    class IAggregator {
        public:
            virtual std::string name() const = 0;
            virtual double aggregate(const std::vector<double>& values) const = 0;
            virtual ~IAggregator() = default;
    };


    class MeanAggregator : public IAggregator {
        public:
            std::string name() const override { return "mean"; }
            double aggregate(const std::vector<double>& values) const override {
                return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
            }
    };


    class MedianAggregator : public IAggregator {
        public:
            std::string name() const override { return "median"; }
            double aggregate(const std::vector<double>& values) const override {
                std::vector<double> sorted = values;
                std::sort(sorted.begin(), sorted.end());
                size_t mid = sorted.size() / 2;
                return sorted.size() % 2 == 0 ? (sorted[mid - 1] + sorted[mid]) / 2.0 : sorted[mid];
            }
    };


    class MinAggregator : public IAggregator {
        public:
            std::string name() const override { return "min"; }
            double aggregate(const std::vector<double>& values) const override {
                return *std::min_element(values.begin(), values.end());
            }
    };

    
    class MaxAggregator : public IAggregator {
        public:
            std::string name() const override { return "max"; }
            double aggregate(const std::vector<double>& values) const override {
                return *std::max_element(values.begin(), values.end());
            }
    };


    template<typename Input, typename Output>
    class ISimulator {
    public:
        virtual Output operator()(const Input& input) const = 0;
        virtual ~ISimulator() = default;
    };


    template<typename Output>
    class IMetric {
    public:
        virtual std::string name() const = 0;
        virtual double extract(const Output&) const = 0;
        virtual ~IMetric() = default;
    };


    template<typename Input>
    class IInputGenerator {
    public:
        virtual Input generate(int size) const = 0;
    };
}
#endif // INTERFACES_HPP

