<?php

namespace Rector\Tests\Php80\Rector\Identical\StrEndsWithRector\Fixture;

class SubstrConst
{
    const BUNDLE = 'value';

    public function run()
    {
        $isMatch = substr($haystack, -5) === self::BUNDLE;

        $isMatch = self::BUNDLE === substr($haystack, -5);
    }
}

?>
-----
<?php

namespace Rector\Tests\Php80\Rector\Identical\StrEndsWithRector\Fixture;

class SubstrConst
{
    const BUNDLE = 'value';

    public function run()
    {
        $isMatch = str_ends_with($haystack, self::BUNDLE);

        $isMatch = str_ends_with($haystack, self::BUNDLE);
    }
}

?>
