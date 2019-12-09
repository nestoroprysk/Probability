class Solution {
public:
    using Vector = vector<double>;
    using Matrix = vector<vector<double>>;
    double knightProbability(const int N, const int K, const int r, const int c) {
        Vector begin(N * N + 1, 0);
        begin[rowColumnToIndex(r, c, N)] = 1;
        Matrix matrix(N * N + 1, vector<double>(N * N + 1, 0));
        for (auto i = 0; i < N * N; ++i) {
            const auto candidates = getCandidates(i, N);
            for (auto j = 0; j < N * N; ++j) {
                if (candidates.find(j) != candidates.end()) {
                    matrix[i][j] = 1.0 / 8;
                }
            }
            matrix[i][N * N] = (8 - 1.0 * candidates.size()) / 8;
        }
        matrix[N * N][N * N] = 1;
        matrix = multiply(matrix, K);
        const auto result = multiplyWithVector(matrix, begin);
        return 1 - result[N * N];
    }
private:
    unordered_set<int> getCandidates(const int i, const int N) {
        unordered_set<int> result;
        const auto r = i / N;
        const auto c = i % N;
        if (withinBoundaries(r - 1, c + 2, N)) {
            result.emplace(rowColumnToIndex(r - 1, c + 2, N));
        }
        if (withinBoundaries(r + 1, c + 2, N)) {
            result.emplace(rowColumnToIndex(r + 1, c + 2, N));
        }
        if (withinBoundaries(r + 2, c + 1, N)) {
            result.emplace(rowColumnToIndex(r + 2, c + 1, N));
        }
        if (withinBoundaries(r + 2, c - 1, N)) {
            result.emplace(rowColumnToIndex(r + 2, c - 1, N));
        }
        if (withinBoundaries(r + 1, c - 2, N)) {
            result.emplace(rowColumnToIndex(r + 1, c - 2, N));
        }
        if (withinBoundaries(r - 1, c - 2, N)) {
            result.emplace(rowColumnToIndex(r - 1, c - 2, N));
        }
        if (withinBoundaries(r - 2, c - 1, N)) {
            result.emplace(rowColumnToIndex(r - 2, c - 1, N));
        }
        if (withinBoundaries(r - 2, c + 1, N)) {
            result.emplace(rowColumnToIndex(r - 2, c + 1, N));
        }
        return result;
    }
    int rowColumnToIndex(const int r, const int c, const int N) {
        return N * r + c;
    }
    bool withinBoundaries(const int r, const int c, const int N) {
        if (r < 0) {
            return false;
        }
        if (c < 0) {
            return false;
        }
        if (r >= N) {
            return false;
        }
        if (c >= N) {
            return false;
        }
        return true;
    }
    Matrix multiply(const Matrix& matrix, const int K) {
        auto result = matrix;
        for (auto i = 0; i < K; ++i) {
            result = multiplyImpl(result, matrix);
        }
        return result;
    }
    Matrix multiplyImpl(const Matrix& lhs, const Matrix& rhs) {
        auto result = lhs;
        for (auto i = 0; i < lhs.size(); ++i) {
            for (auto j = 0; j < lhs[i].size(); ++j) {
                auto sum = 0.0;
                for (auto k = 0; k < lhs.size(); ++k) {
                    sum += lhs[i][k] * rhs[j][k];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }
    Vector multiplyWithVector(const Matrix& m, const Vector& v) {
        auto result = v;
        for (auto i = 0; i < v.size(); ++i) {
            auto sum = 0.0;
            for (auto k = 0; k < m.size(); ++k) {
                sum += m[i][k] * v[k];
            }
            result[i] = sum;
        }
        return result;
    }
};
