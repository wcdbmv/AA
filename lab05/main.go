package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	TasksNumber = 3
)

type Task struct {
	Value       int
	Result      int
	StartTimes  []time.Time
	EndTimes    []time.Time
}

type job func(in, out chan interface{})

func ExecutePipeline(jobs ...job) {
	wg := &sync.WaitGroup{}
	in := make(chan interface{}, TasksNumber)
	for i := range jobs {
		out := make(chan interface{}, TasksNumber)
		wg.Add(1)
		go func(function job, in, out chan interface{}) {
			defer wg.Done()
			defer close(out)
			function(in, out)
		}(jobs[i], in, out)
		in = out
	}
	wg.Wait()
}

func dataGenerator(_, out chan interface{}) {
	s := rand.NewSource(time.Now().UnixNano())
	r := rand.New(s)
	for i := 0; i < TasksNumber; i++ {
		val := r.Intn(100)
		task := Task{Value: val, Result: val}
		out <- task
	}
}

func makeHandler(sleepDuration int, multiplier int) func(chan interface{}, chan interface{}) {
	return func(in, out chan interface{}) {
		for rawTask := range in {
			task := rawTask.(Task)
			task.StartTimes = append(task.StartTimes, time.Now())

			task.Result *= multiplier
			time.Sleep(time.Millisecond * time.Duration(sleepDuration))

			task.EndTimes = append(task.EndTimes, time.Now())
			out <- task
		}
	}
}

func logHandler(in, _ chan interface{}) {
	for rawTask := range in {
		task := rawTask.(Task)
		fmt.Printf("Task's start value = %d, result = %d\n", task.Value, task.Result)
		fmt.Printf("Start 1st: %s, end 1st: %s\n", task.StartTimes[0].Local(), task.EndTimes[0].Local())
		fmt.Printf("Start 2nd: %s, end 2nd: %s\n", task.StartTimes[1].Local(), task.EndTimes[1].Local())
		fmt.Printf("Start 3d: %s, end 3d: %s\n", task.StartTimes[2].Local(), task.EndTimes[2].Local())
		fmt.Println()
	}
}

func main() {
	jobs := []job{
		job(dataGenerator),
		job(makeHandler(100, 2)),
		job(makeHandler(200, 3)),
		job(makeHandler(300, 2)),
		job(logHandler),
	}

	start := time.Now()
	ExecutePipeline(jobs...)
	end := time.Since(start)

	fmt.Printf("All time: %s\n", end)
}
