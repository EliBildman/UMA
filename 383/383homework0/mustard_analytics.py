#!/usr/bin/python
import sys
import csv
import datetime
import calendar


  
# COMPSCI 383 Homework 0 
#  
# Fill in the bodies of the missing functions as specified by the comments and docstrings.


# Exercise 0. (8 points)
#  
def read_data(file_name):
    """Read in the csv file and return a list of tuples representing the data.

    Transform each field as follows:
      date: datetime.date
      mileage: integer
      location: string
      gallons: float
      price: float (you'll need to get rid of the '$')

    Do not return a tuple for the header row.  While you can process the raw text using string
    functions, to receive full credit you must use Python's built in csv module.

    If the field is blank, you should put a None value in the tuple for that field (for the 
    other functions below, you'll need to check for None values when making calculations).  

    Hint: to parse the date field, use the strptime function in the datetime module, and then
    use datetime.date() to create a date object.

    See: 
      https://docs.python.org/3/library/csv.html
      https://docs.python.org/3/library/datetime.html

    """
    rows = []  # this list should contain one tuple per row
    
    with open(file_name) as file:

      data = csv.reader(file)
      data.__next__()
      for row in data:
        
        date = datetime.datetime.strptime( row[0], '%m/%d/%Y' ).date() if row[0] != '' else None       

        mileage = int(row[1]) if row[1] != '' else None
          
        location = row[2] if row[2] != '' else None

        gallons = float(row[3]) if row[3] != '' else None

        price = float( row[4][1:] ) if row[4] != '' else None
                  
        rows.append((date, mileage, location, gallons, price))

    return rows


# Exercise 1. (5 points)
#
def total_cost(rows):
    """Return the total amount of money spent on gas as a float.
    
    Hint: calculate by multiplying the price per gallon with the  number of gallons for each row.
    """
    total = 0.0  # delete this

    for row in rows:
      if(row[3] == None or row[4] == None):
        continue
      total += row[3] * row[4]

    return total


# Exercise 2. (5 points)
#
def num_single_locs(rows):
    """Return the number of refueling locations that were visited exactly once.
    
    Hint: store the locations and counts (as keys and values, respectively) in a dictionary, 
    then count up the number of entries with a value equal to one.  
    """
    stations = {}

    for row in rows:

      if row[2] == None:
        continue

      if row[2] in stations:
        stations[row[2]] += 1
      else:
        stations[row[2]] = 1
    
    ones = 0

    for station in stations:
      if stations[station] == 1:
        ones += 1

    return ones


# Exercise 3. (8 points)
#
def most_common_locs(rows):
    """Return a list of the 10 most common refueling locations, along with the number of times
    they appear in the data, in descending order.  
    
    Each list item should be a two-element tuple of the form (name, count).  For example, your
    function might return a list of the form: 
      [ ("Honolulu, HI", 42), ("Shermer, IL", 19), ("Box Elder, MO"), ... ]

    Hint: store the locations and counts in a dictionary as above, then convert the dictionary 
    into a list of tuples using the items() method.  Sort the list of tuples using sort() or 
    sorted().

    See:
      https://docs.python.org/3/tutorial/datastructures.html#dictionaries
      https://docs.python.org/3/howto/sorting.html#key-functions
    """
    
    stations = {}

    for row in rows:
      
      if row[2] == None:
        continue

      if row[2] in stations:
        stations[row[2]] += 1
      else:
        stations[row[2]] = 1
    
    station_tuples = []

    for station in stations:
      station_tuples.append( (station, stations[station]) )

    station_tuples.sort(key= lambda station_tup: station_tup[1], reverse=True)

    return station_tuples[:10]


# Exercise 4. (8 points)
#
def state_totals(rows):
    """Return a dictionary containing the total number of visits (value) for each state as 
    designated by the two-letter abbreviation at the end of the location string (keys).  

    The return value should be a Python dictionary of the form:
      { "CA": 42, "HI": 19, "MA": 8675309, ... }

    Hint: to do this, you'll need to pull apart the location string and extract the state 
    abbreviation.  Note that some of the entries are malformed, and containing a state code but no
    city name.  You still want to count these cases (of course, if the location is blank, ignore
    the entry.
    """
    state__count = {}
    
    for row in rows:

      if row[2] == None:
        continue

      state = row[2][-2:]

      if state in state__count:
        state__count[state] += 1
      else:
        state__count[state] = 1

    return state__count


# Exercise 5. (8 points)
#
def num_unique_dates(rows):
    """Return the total number unique dates in the calendar that refueling took place.

    That is, if you ignore the year, how many different days had entries? (This number should be 
    less than or equal to 366!)
 
    Hint: the easiest way to do this is create a token representing the calendar day.  These could
    be strings (using strftime()) or integers (using date.toordinal()).  Store them in a Python set
    as you go, and then return the size of the set.

    See:
      https://docs.python.org/3/library/datetime.html#date-objects
    """
    unique_dates = []

    for row in rows:

      if row[0] == None:
        continue

      found = False

      for date in unique_dates:
        if date.month == row[0].month and date.day == row[0].day:
          found = True
          break
      
      if not found:
        unique_dates.append(row[0])

    return len(unique_dates)


# Exercise 6. (8 points)
#
def month_avg_price(rows):
    """Return a dictionary containing the average price per gallon as a float (values) for each 
    month of the year (keys).

    The dictionary you return should have 12 entries, with full month names as keys, and floats as
    values.  For example:
        { "January": 3.12, "February": 2.89, ... }

    See:
      https://docs.python.org/3/library/datetime.html
    """
    totals = []

    for _ in range(12):
      # ( total, n )
      totals.append( [0.0, 0.0] )

    for row in rows:

      if row[0] == None or row[4] == None:
        continue

      totals[row[0].month - 1][0] += row[4]
      totals[row[0].month - 1][1] += 1

    monthly_avg = {}

    for i in range(len(totals)):
      monthly_avg[calendar.month_name[i + 1]] = totals[i][0] / totals[i][1] if totals[i][1] != 0 else 0

    return monthly_avg


# EXTRA CREDIT (+10 points)
#
def highest_thirty(rows):
    """Return the start and end dates for top three thirty-day periods with the most miles driven.

    The periods should not overlap.  You should find them in a greedy manner; that is, find the
    highest mileage thirty-day period first, and then select the next highest that is outside that
    window).
    
    Return a list with the start and end dates (as a Python datetime object) for each period, 
    followed by the total mileage, stored in a tuple:  
        [ (1995-02-14, 1995-03-16, 502),
          (1991-12-21, 1992-01-16, 456),
          (1997-06-01, 1997-06-28, 384) ]
    """
    
    #easiest way i could think to sort the rows by date (i think theyre already sorted but prolly cant assume that)

    rows = sorted(rows, key= lambda row: datetime.date(1, 1, 1) if (row[0] == None or row[1] == None) else row[0] )

    i = 0
    while rows[i][0] == None or rows[i][1] == None:
      del rows[i]

    def find_thrity_period(i):
      start_ind = i
      while i + 1 < len(rows) and rows[i + 1][0] - rows[start_ind][0] <= datetime.timedelta(days=30):
        i += 1
      return (rows[start_ind][0], rows[i][0], rows[i][1] - rows[start_ind][1], start_ind)

    def remove_thirty_period(i):
      start_time = rows[i][0]
      while i < len(rows) and rows[i][0] - start_time <= datetime.timedelta(days=30):
        del rows[i]

    def find_and_remove_greatest():
      max_period = (None, None, None, 0)

      for i in range(len(rows)):

        period = find_thrity_period(i)
        if max_period[0] == None or period[2] > max_period[2]:
          max_period = period

      remove_thirty_period(max_period[3])

      return (max_period[0], max_period[1], max_period[2])

    return (find_and_remove_greatest() for i in range(3))


# The main() function below will be executed when your program is run.
# Note that Python does not require a main() function, but it is
# considered good style (as is including the __name__ == '__main__'
# conditional below)
#
def main(file_name):
    rows = read_data(file_name)
    print("Exercise 0: {} rows\n".format(len(rows)))

    cost = total_cost(rows)
    print("Exercise 1: ${:.2f}\n".format(cost))

    singles = num_single_locs(rows)
    print("Exercise 2: {}\n".format(singles))

    print("Exercise 3:")
    for loc, count in most_common_locs(rows):
        print("\t{}\t{}".format(loc, count))
    print("")

    print("Exercise 4:")
    for state, count in sorted(state_totals(rows).items()):
        print("\t{}\t{}".format(state, count))
    print("")

    unique_count = num_unique_dates(rows)
    print("Exercise 5: {}\n".format(unique_count))

    print("Exercise 6:")
    for month, price in sorted(month_avg_price(rows).items(),
                               key=lambda t: datetime.datetime.strptime(t[0], '%B').month):
        print("\t{}\t${:.2f}".format(month, price))
    print("")

    print("Extra Credit:")
    for start, end, miles in sorted(highest_thirty(rows)):
        print("\t{}\t{}\t{} miles".format(start.strftime("%Y-%m-%d"),
                                          end.strftime("%Y-%m-%d"), miles))
    print("")


#########################

if __name__ == '__main__':
    
    data_file_name = "test_data.csv" 
    main(data_file_name)




